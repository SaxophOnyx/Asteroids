#include "LargeAsteroid.h"
#include "Player.h"
#include "SmallAsteroid.h"
#include "PlayerProjectile.h"
#include "LargeAsteroidDestroyedEvent.h"

namespace ast
{
    HPEN LargeAsteroid::colliderPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 255));

    LargeAsteroid::LargeAsteroid(IEventInput& eventInput)
        : AsteroidBase(eventInput, 75)
    {

    }

    void LargeAsteroid::update(double dt)
    {
        processCollisions(dt);

        pos.x += velocity.x * dt;
        pos.y += velocity.y * dt;
    }

    void LargeAsteroid::render(HDC hdc)
    {
        HPEN oldPen = (HPEN)SelectObject(hdc, colliderPen);
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));

        Ellipse(hdc, pos.x - collider, pos.y - collider, pos.x + collider, pos.y + collider);

        SelectObject(hdc, oldBrush);
        SelectObject(hdc, oldPen);
    }

    long LargeAsteroid::getTypeId()
    {
        return LargeAsteroid::TYPE_ID;
    }

    int LargeAsteroid::getDamage()
    {
        return 40;
    }

    void LargeAsteroid::processCollisions(double dt)
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

    void LargeAsteroid::collideWithSmallAsteroid(double dt, SmallAsteroid& asteroid)
    {

    }

    void LargeAsteroid::collideWithLargeAsteroid(double dt, LargeAsteroid& asteroid)
    {
        velocity.x *= -1;
        velocity.y *= -1;
    }

    void LargeAsteroid::collideWithPlayerProjectile(double dt, PlayerProjectile& proj)
    {
        if (!isDead())
        {
            LargeAsteroidDestroyedEvent* e = new LargeAsteroidDestroyedEvent(*this, true);
            eventInput.enque(e);
            die();
        }
    }

    void LargeAsteroid::collideWithPlayer(double dt, Player& player)
    {
        if (!isDead())
        {
            LargeAsteroidDestroyedEvent* e = new LargeAsteroidDestroyedEvent(*this, false);
            eventInput.enque(e);
            die();
        }
    }
}
