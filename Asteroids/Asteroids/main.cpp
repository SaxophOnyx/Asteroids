#include <windows.h>
#include "StateMachine.h"
#include "MainMenuState.h"
#include "GameOverState.h"
#include "SimpleResourceManager.h"

#define UPDATES_PER_SECOND 60
#define FRAMES_PER_SECOND 90
#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void initializeResourceManager();
void update(double dt);
void render();

bool isRunning;
std::string resourcePath = "D:\\asteroidsResources";
ast::SimpleResourceManager* resourceManager;
ast::StateMachine* stateMachine;
HWND windowHandle;
POINT currMousePos;
RECT* windowRect;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    const LPCWSTR WINDOW_CLASS_NAME = L"AsteroidsWindowClass";
    const LPCWSTR WINDOW_NAME = L"Asteroids!";

    //регистрация оконного класса
    WNDCLASS wnd = { };
    if (!GetClassInfo(hInstance, WINDOW_CLASS_NAME, &wnd))
    {
        WNDCLASS wc = { };
        wc.lpfnWndProc = WindowProc;
        wc.hInstance = hInstance;
        wc.lpszClassName = WINDOW_CLASS_NAME;
        RegisterClass(&wc);
    }

    //создание окна
    windowHandle = CreateWindowEx(0, WINDOW_CLASS_NAME, WINDOW_NAME, WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT,
        NULL, NULL, hInstance, NULL);

    //вызов "конструктора"
    initializeResourceManager();
    stateMachine = new ast::StateMachine();
    windowRect = new RECT();
    GetClientRect(windowHandle, windowRect);

    //создание начального игрового состояния
    ast::MainMenuState* state = new ast::MainMenuState(*resourceManager, *windowRect);
    stateMachine->push(state);

    //запуск
    isRunning = true;
    ShowWindow(windowHandle, nCmdShow);
    MSG msg = { };
    ULONGLONG lastUpdateTick = GetTickCount64();
    ULONGLONG lastRenderTick = lastUpdateTick;
    while (isRunning)
    {
        while (PeekMessage(&msg, windowHandle, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        ULONGLONG currTick = GetTickCount64();
        if ((currTick - lastUpdateTick) >= (1000.f / UPDATES_PER_SECOND))
        {
            double dt_ms = 1.f / UPDATES_PER_SECOND;
            lastUpdateTick = currTick;
            update(dt_ms);
        }

        if ((currTick - lastRenderTick) >= (1000.f / FRAMES_PER_SECOND))
        {
            lastRenderTick = currTick;
            InvalidateRect(windowHandle, NULL, true);
        }
    }

    return 0;
}

LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
            PostQuitMessage(0);
            isRunning = false;
            return 0;

        case WM_PAINT:
            render();
            return 0;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

void initializeResourceManager()
{
    resourceManager = new ast::SimpleResourceManager(resourcePath);
    resourceManager->loadImage("gamestate_background", "gamestate_background.bmp");
    resourceManager->loadImage("mainmenustate_background", "mainmenustate_background.bmp");
    resourceManager->loadImage("gameover_background", "gameover_background.bmp");

    resourceManager->loadBrush("default_gui_background", CreateSolidBrush(RGB(48, 32, 120)));
    resourceManager->loadBrush("button_hover_background", CreateSolidBrush(RGB(50, 110, 75)));
    resourceManager->loadBrush("button_pressed_background", CreateSolidBrush(RGB(150, 32, 75)));
    resourceManager->loadBrush("transparent_brush", (HBRUSH)GetStockObject(HOLLOW_BRUSH));

    resourceManager->loadPen("default_gui_pen", CreatePen(PS_SOLID, 5, RGB(236, 200, 76)));
    resourceManager->loadPen("empty_pen", CreatePen(PS_NULL, 0, RGB(0, 0, 0)));

    resourceManager->loadColor("default_gui_text_color", RGB(236, 200, 76));
    
    HFONT mainMenuFont = CreateFont(40, 0, 0, 0, FW_BOLD | FS_ARABIC, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"Consolas");
    resourceManager->loadFont("mainmenustate_gui_font", mainMenuFont);

    HFONT gameStateGuiFont = CreateFont(40, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"Consolas");
    resourceManager->loadFont("gamestate_gui_font", gameStateGuiFont);

    HFONT gameOverStateButtonFont = CreateFont(40, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"Consolas");
    resourceManager->loadFont("gameoverstate_gui_buttonFont", gameOverStateButtonFont);

    HFONT headerFont = CreateFont(88, 0, 0, 0, FW_BLACK, 0, 1, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"Consolas");
    resourceManager->loadFont("default_header_font", headerFont);

    HFONT largeFont = CreateFont(48, 0, 0, 0, FW_BLACK, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"Consolas");
    resourceManager->loadFont("default_large_font", largeFont);
}

void update(double dt)
{
    GetCursorPos(&currMousePos);
    ScreenToClient(windowHandle, &currMousePos);

    if (!stateMachine->isEmpty())
    {
        stateMachine->update(dt, currMousePos);
        //InvalidateRect(windowHandle, NULL, true);
    }
    else
    {
        PostMessage(windowHandle, WM_CLOSE, 0, 0);
    }
}

void render()
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(windowHandle, &ps);
    HDC memDc = CreateCompatibleDC(hdc);
    RECT clientRect;
    GetClientRect(windowHandle, &clientRect);
    HBITMAP bmp = CreateCompatibleBitmap(hdc, clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);
    HBITMAP oldBmp = (HBITMAP)SelectObject(memDc, bmp);

    FillRect(memDc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
    SetBkMode(memDc, TRANSPARENT);

    if (!stateMachine->isEmpty())
        stateMachine->render(memDc);

    BitBlt(hdc, 0, 0, clientRect.right - clientRect.left, clientRect.bottom - clientRect.top, memDc, 0, 0, SRCCOPY);
    SelectObject(memDc, oldBmp);
    DeleteObject(bmp);
    DeleteObject(memDc);
    EndPaint(windowHandle, &ps);
}
