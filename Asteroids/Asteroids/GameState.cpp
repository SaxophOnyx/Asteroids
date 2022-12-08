#include "GameState.h"
#include <ctime>
#include <random>
#include <cmath>
#include "Player.h"
#include "PlayerDiedEvent.h"
#include "GameOverState.h"
#include "PlayerShotEvent.h"
#include "SmallAsteroidDestroyedEvent.h"
#include "LargeAsteroidDestroyedEvent.h"
#include "AddMath.h"

namespace ast
{
    GameState::GameState(ISimpleResourceManager& resourceManager, RECT& windowBorders)
        : State(resourceManager, windowBorders),
        objectFactory(resourceManager, eventBus),
        collisionSystem(windowBorders),
        asteroidSpawnTimer(2000),
        asteroidsCount(0), maxAsteroidCount(15),
        playerScore(0), playerTime(0.f)
    {
        initGui();
        this->background = this->resourceManager.getImage("gamestate_background");

        srand(time(NULL));
        initPlayer();
    }

    GameState::~GameState()
    {
        delete(scoreCounter);
        delete(exitButton);
    }

    void GameState::update(double dt, POINT& mousePos)
    {
        exitButton->update(dt, mousePos);
        if (exitButton->isPressed())
        {
            die();
            return;
        }

        updateTimers(dt);
        collisionSystem.update(dt);

        for (int i = 0; i < this->gameObjects.size(); ++i)
        {
            GameObject* obj = this->gameObjects.at(i);
            obj->update(dt);
        }

        processObjectEvents(dt);
        collisionSystem.removeDeadObjects();
        removeDeadObjects();
        scoreCounter->update(playerScore);
    }

    void GameState::render(HDC hdc)
    {
        this->renderBackground(hdc);
        for (int i = 0; i < this->gameObjects.size(); ++i)
        {
            GameObject* obj = this->gameObjects.at(i);
            obj->render(hdc);
        }

        scoreCounter->render(hdc);
        exitButton->render(hdc);
    }

    void GameState::initGui()
    {
        HFONT font = resourceManager.getFont("gamestate_gui_font");
        HPEN pen = resourceManager.getPen("default_gui_pen");
        HBRUSH hover = resourceManager.getBrush("button_hover_background");
        HBRUSH pressed = resourceManager.getBrush("button_pressed_background");
        HBRUSH transparent = resourceManager.getBrush("transparent_brush");
        COLORREF textColor = resourceManager.getColor("default_gui_text_color");

        int offset = 20;

        int buttonWidth = 140;
        int buttonHeight = 70;
        int buttonLeft = windowBorders.right - buttonWidth - offset;
        int buttonTop = windowBorders.top + offset;
        exitButton = new Button(buttonLeft, buttonTop, buttonLeft + buttonWidth, buttonTop + buttonHeight, "Exit");
        exitButton->setBorderPen(pen);
        exitButton->setFont(font);
        exitButton->setIdleBackgroundBrush(transparent);
        exitButton->setHoverBackgroundBrush(hover);
        exitButton->setPressedBackgroundBrush(pressed);
        exitButton->setTextColor(textColor);

        int counterWidth = 450;
        int counterHeight = 70;
        int counterLeft = buttonLeft - offset - counterWidth;
        int counterTop = buttonTop;
        scoreCounter = new LabeledCounter(counterLeft, counterTop, counterLeft + counterWidth, counterTop + counterHeight, "Score");
        scoreCounter->setBackgroundBrush(transparent);
        scoreCounter->setBorderPen(pen);
        scoreCounter->setFont(font);
        scoreCounter->setTextColor(textColor);
    }

    void GameState::initPlayer()
    {
        Player* player = new Player(eventBus);
        double posX = (windowBorders.right - windowBorders.left) / 2 + windowBorders.left;
        double posY = (windowBorders.bottom - windowBorders.top) / 2 + windowBorders.top;
        player->setPosition(posX, posY);
        gameObjects.push_back(player);
        collisionSystem.addObject(*player);
    }

    void GameState::removeDeadObjects()
    {
        int i = 0;
        int currSize = gameObjects.size();
        while (i < currSize)
        {
            if (gameObjects.at(i)->isDead())
            {
                gameObjects.at(i) = gameObjects.at(currSize - 1);
                gameObjects.pop_back();
                --currSize;
            }
            else
                ++i;
        }
    }

    void GameState::updateTimers(double dt)
    {
        asteroidSpawnTimer.update(dt);
        if (asteroidSpawnTimer.isElapsed())
        {
            if (asteroidsCount < maxAsteroidCount)
                spawnAsteroid();

            asteroidSpawnTimer.reset();
        }

        playerTime += dt;
    }

    void GameState::processObjectEvents(double dt)
    {
        while (!eventBus.isEmpty())
        {
            EventBase* e = eventBus.deque();
            long id = e->getTypeId();

            switch (id)
            {
                case PlayerDiedEvent::TYPE_ID:
                {
                    GameOverState* s = new GameOverState(resourceManager, windowBorders, playerScore, playerTime);
                    setNewState(s);
                    die();
                    break;
                }

                case PlayerShotEvent::TYPE_ID:
                {
                    PlayerShotEvent* playerShotEvent = static_cast<PlayerShotEvent*>(e);
                    Player& player = playerShotEvent->getPlayer();
                    spawnPlayerProjectile(player);
                    break;
                }

                case SmallAsteroidDestroyedEvent::TYPE_ID:
                {
                    --asteroidsCount;
                    SmallAsteroidDestroyedEvent* smallAsteroidDestroyedEvent = static_cast<SmallAsteroidDestroyedEvent*>(e);
                    if (smallAsteroidDestroyedEvent->byPlayer())
                    {
                        playerScore += 100;
                    }

                    break;
                }

                case LargeAsteroidDestroyedEvent::TYPE_ID:
                {
                    --asteroidsCount;
                    LargeAsteroidDestroyedEvent* largeAsteroidDestroyedEvent = static_cast<LargeAsteroidDestroyedEvent*>(e);
                    LargeAsteroid& asteroid = largeAsteroidDestroyedEvent->getAsteroid();
                    spawnLargeAsteroidShatters(asteroid);

                    if (largeAsteroidDestroyedEvent->byPlayer())
                    {
                        playerScore += 150;
                    }

                    break;
                }
            }

            delete(e);
        }
    }

    void GameState::renderBackground(HDC hdc)
    {
        LONG topLeftX = this->windowBorders.left;
        LONG topLeftY = this->windowBorders.top;
        LONG bottomRightX = this->windowBorders.right;
        LONG bottomRightY = this->windowBorders.bottom;

        HDC bitmapDC = CreateCompatibleDC(hdc);
        HBITMAP oldBitmap = (HBITMAP)SelectObject(bitmapDC, this->background);
        BitBlt(hdc, topLeftX, topLeftY, bottomRightX, bottomRightY, bitmapDC, 0, 0, SRCCOPY);
        SelectObject(bitmapDC, oldBitmap);
        DeleteObject(bitmapDC);
    }

    void GameState::spawnAsteroid()
    {
        AsteroidBase* ast;
        double velocityModulo;

        if (rand() % 5 == 0)
        {
            ast = objectFactory.getLargeAsteroid();
            velocityModulo = rand() % 201 + 50;
        }
        else
        {
            ast = objectFactory.getSmallAsteroid();
            velocityModulo = rand() % 251 + 150;
        }

        double centerX = windowBorders.left + (windowBorders.right - windowBorders.left) / 2;
        double centerY = windowBorders.top + (windowBorders.bottom - windowBorders.top) / 2;
        long minX = windowBorders.left + 1;
        long maxX = windowBorders.right - 1;
        long minY = windowBorders.top + 1;
        long maxY = windowBorders.bottom - 1;

        Point spawn;
        Point dest;

        int side = rand() % 4;
        switch (side)
        {
            case 0:
                spawn.x = rand() % (maxX - minX) + minX;
                spawn.y = minY - ast->getCollider();
                dest.x = rand() % (maxX - minX) + minX;
                dest.y = maxY;
                break;

            case 1:
                spawn.x = maxX + ast->getCollider();
                spawn.y = rand() % (maxY - minY) + minY;
                dest.x = minX;
                dest.y = rand() % (maxY - minY) + minY;
                break;

            case 2:
                spawn.x = rand() % (maxX - minX) + minX;
                spawn.y = maxY + ast->getCollider();
                dest.x = rand() % (maxX - minX) + minX;
                dest.y = minY;
                break;

            case 3:
                spawn.x = minX - ast->getCollider();
                spawn.y = rand() % (maxY - minY) + minY;
                dest.x = maxX;
                dest.y = rand() % (maxY - minY) + minY;
                break;
        }

        Vector2 vel(spawn.x, spawn.y, dest.x, dest.y);
        vel.normalize();

        vel.x *= velocityModulo;
        vel.y *= velocityModulo;

        ast->setPosition(spawn);
        ast->setVelocity(vel);
        gameObjects.push_back(ast);
        collisionSystem.addObject(*ast);
        ++asteroidsCount;
    }

    void GameState::spawnPlayerProjectile(Player& player)
    {
        PlayerProjectile* proj = objectFactory.getPlayerProjectile();
        double projCollider = proj->getCollider();

        double angle = player.getAngle();
        double playerCollider = player.getCollider();
        auto& pos = player.getPosition();
        auto& vel = player.getVelocity();

        double x = (playerCollider + projCollider) * std::cos(angle);
        double y = (playerCollider + projCollider) * std::sin(angle);
        double projVelX = 350 * std::cos(angle) + vel.x;
        double projVelY = 350 * std::sin(angle) + vel.y;

        proj->setPosition(pos.x + x * 1.25f, pos.y + y * 1.25f);
        proj->setVelocity(projVelX, projVelY);

        gameObjects.push_back(proj);
        collisionSystem.addObject(*proj);
    }

    void GameState::spawnLargeAsteroidShatters(LargeAsteroid& asteroid)
    {
        auto& pos = asteroid.getPosition();
        auto& vel = asteroid.getVelocity();
        double collider = asteroid.getCollider();

        Point shatterPos{};
        Vector2 shatterVel{};
        int shatterNumber = 3;
        double angle = 0.f;
        double shatterVelModulo = 450;
        double deltaAngle = std::_Pi / shatterNumber * 2;

        for (int i = 0; i < shatterNumber; ++i)
        {
            SmallAsteroid* shatter = objectFactory.getSmallAsteroid();
            shatterPos.x = std::cos(angle) * (collider + shatter->getCollider()) * 1.25f + pos.x;
            shatterPos.y = std::sin(angle) * (collider + shatter->getCollider()) * 1.25f + pos.y;
            shatterVel.x = std::cos(angle) * shatterVelModulo + vel.x;
            shatterVel.y = std::sin(angle) * shatterVelModulo + vel.y;
            shatter->setPosition(shatterPos);
            shatter->setVelocity(shatterVel);

            gameObjects.push_back(shatter);
            collisionSystem.addObject(*shatter);
            angle += deltaAngle;
        }
    }
}
