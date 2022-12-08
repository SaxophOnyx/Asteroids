#include "Player.h"
#include <cmath>
#include "PlayerShotEvent.h"
#include "SmallAsteroid.h"
#include "LargeAsteroid.h"
#include "PlayerDiedEvent.h"

namespace ast
{
    HPEN Player::colliderPen = CreatePen(PS_SOLID, 5, RGB(0, 255, 0));

    HPEN Player::trajectoryPen = CreatePen(PS_DOT, 1, RGB(255, 0, 0));

    Player::Player(IEventInput& eventInput)
        : CollidableObject(50), eventInput(eventInput), angle(0.f), shootingTimer(2000), health(100)
    {
        shootingTimer.setToZero();
    }

    Player::~Player()
    {

    }

    void Player::update(double dt)
    {
        processCollisions(dt);

        shootingTimer.update(dt);

        handleRotationInput(dt);
        handleAccelerationInput(dt);
        handleShootingInput(dt);

        pos.x += velocity.x * dt;
        pos.y += velocity.y * dt;
    }

    void Player::render(HDC hdc)
    {
        HPEN oldPen = (HPEN)SelectObject(hdc, trajectoryPen);
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));

        int x = collider * std::cos(angle);
        int y = collider * std::sin(angle);
        POINT p;

        MoveToEx(hdc, pos.x + x, pos.y + y, &p);
        LineTo(hdc, pos.x + x * TRAJECTORY_MULTIPLIER, pos.y + y * TRAJECTORY_MULTIPLIER);

        SelectObject(hdc, colliderPen);

        MoveToEx(hdc, pos.x + x, pos.y + y, NULL);
        Ellipse(hdc, pos.x - collider, pos.y - collider, pos.x + collider, pos.y + collider);
        LineTo(hdc, pos.x + x * ARROW_MULTIPLIER, pos.y + y * ARROW_MULTIPLIER);
        MoveToEx(hdc, p.x, p.y, NULL);

        SelectObject(hdc, oldBrush);
        SelectObject(hdc, oldPen);
    }

    long Player::getTypeId()
    {
        return TYPE_ID;
    }

    double Player::getAngle()
    {
        return angle;
    }

    void Player::setAngle(double angle)
    {
        this->angle = angle;
    }

    void Player::handleRotationInput(double dt)
    {
        short left = GetKeyState(VK_LEFT);
        short right = GetKeyState(VK_RIGHT);

        if (left < 0 && right < 0)
            return;

        if (left < 0)
            angle -= 4 * dt;
        else if (right < 0)
            angle += 4 * dt;
    }

    void Player::handleAccelerationInput(double dt)
    {
        short forward = GetKeyState(VK_UP);
        short backward = GetKeyState(VK_DOWN);

        if (forward < 0 && backward < 0)
            return;

        if (forward < 0)
        {
            velocity.x += (400 * cos(angle) * dt);
            velocity.y += (400 * sin(angle) * dt);
        }
        else if (backward < 0)
        {
            velocity.x = velocity.x * (1 - dt) * 0.95;
            velocity.y = velocity.y * (1 - dt) * 0.95;

            if (fabs(velocity.x) < 0.33 && fabs(velocity.y) < 0.33)
            {
                velocity.x = 0.f;
                velocity.y = 0.f;
            }
        }
    }

    void Player::handleShootingInput(double dt)
    {
        short space = GetKeyState(VK_SPACE);
        if (space < 0)
        {
            if (shootingTimer.isElapsed())
            {
                PlayerShotEvent* e = new PlayerShotEvent(*this);
                eventInput.enque(e);
                shootingTimer.reset();
            }
        }
    }

    void Player::processCollisions(double dt)
    {
        while (!collisionBuffer.empty())
        {
            CollidableObject* obj = collisionBuffer.front();
            long id = obj->getTypeId();

            switch (id)
            {
                case SmallAsteroid::TYPE_ID:
                {
                    SmallAsteroid* asteroid = static_cast<SmallAsteroid*>(obj);
                    int damage = asteroid->getDamage();

                    if (health > damage)
                        health -= damage;
                    else
                    {
                        health = 0;
                        PlayerDiedEvent* diedEvent = new PlayerDiedEvent(*this);
                        eventInput.enque(diedEvent);
                    }

                    break;
                }

                case LargeAsteroid::TYPE_ID:
                {
                    LargeAsteroid* asteroid = static_cast<LargeAsteroid*>(obj);
                    int damage = asteroid->getDamage();

                    if (health > damage)
                        health -= damage;
                    else
                    {
                        health = 0;
                        PlayerDiedEvent* diedEvent = new PlayerDiedEvent(*this);
                        eventInput.enque(diedEvent);
                    }


                    break;
                }
            }

            collisionBuffer.pop();
        }
    }
}
