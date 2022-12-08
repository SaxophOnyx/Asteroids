#include "SmallAsteroid.h"
#include "LargeAsteroid.h"
#include "Player.h"
#include "PlayerProjectile.h"
#include "SmallAsteroidDestroyedEvent.h"

namespace ast
{
    HPEN SmallAsteroid::colliderPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));

    SmallAsteroid::SmallAsteroid(IEventInput& eventInput)
        : AsteroidBase(eventInput, 35)
    {

    }

    void SmallAsteroid::update(double dt)
    {
        processCollisions(dt);

        pos.x += velocity.x * dt;
        pos.y += velocity.y * dt;
    }

    void SmallAsteroid::render(HDC hdc)
    {
        HPEN oldPen = (HPEN)SelectObject(hdc, colliderPen);
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));

        Ellipse(hdc, pos.x - collider, pos.y - collider, pos.x + collider, pos.y + collider);

        SelectObject(hdc, oldBrush);
        SelectObject(hdc, oldPen);
    }

    long SmallAsteroid::getTypeId()
    {
        return SmallAsteroid::TYPE_ID;
    }

    int SmallAsteroid::getDamage()
    {
        return 25;
    }

    void SmallAsteroid::processCollisions(double dt)
    {
        while (!collisionBuffer.empty())
        {
            CollidableObject* obj = collisionBuffer.front();
            long id = obj->getTypeId();

            switch (id)
            {
                case SmallAsteroid::TYPE_ID:
                    collideWithSmallAsteroid(dt, static_cast<SmallAsteroid&>(*obj));
                    break;

                case LargeAsteroid::TYPE_ID:
                    collideWithLargeAsteroid(dt, static_cast<LargeAsteroid&>(*obj));
                    break;

                case Player::TYPE_ID:
                    collideWithPlayer(dt, static_cast<Player&>(*obj));
                    break;

                case PlayerProjectile::TYPE_ID:
                    collideWithPlayerProjectile(dt, static_cast<PlayerProjectile&>(*obj));
                    break;
            }

            collisionBuffer.pop();
        }
    }

    void SmallAsteroid::collideWithSmallAsteroid(double dt, SmallAsteroid& a)
    {
        velocity.y *= -1;
        velocity.x *= -1;
    }

    void SmallAsteroid::collideWithLargeAsteroid(double dt, LargeAsteroid& a)
    {
        if (!isDead())
        {
            SmallAsteroidDestroyedEvent* e = new SmallAsteroidDestroyedEvent(*this, false);
            eventInput.enque(e);
            die();
        }
    }

    void SmallAsteroid::collideWithPlayerProjectile(double dt, PlayerProjectile& p)
    {
        if (!isDead())
        {
            SmallAsteroidDestroyedEvent* e = new SmallAsteroidDestroyedEvent(*this, true);
            eventInput.enque(e);
            die();
        }
    }

    void SmallAsteroid::collideWithPlayer(double dt, Player& p)
    {
        if (!isDead())
        {
            SmallAsteroidDestroyedEvent* e = new SmallAsteroidDestroyedEvent(*this, false);
            eventInput.enque(e);
            die();
        }
    }
}
