#include "PlayerProjectile.h"

namespace ast
{
    HPEN PlayerProjectile::colliderPen = CreatePen(PS_SOLID, 5, RGB(255, 255, 0));

    PlayerProjectile::PlayerProjectile()
        : CollidableObject(20)
    {

    }

    void PlayerProjectile::update(double dt)
    {
        processCollisions(dt);

        pos.x += velocity.x * dt;
        pos.y += velocity.y * dt;
    }

    void PlayerProjectile::render(HDC hdc)
    {
        HPEN oldPen = (HPEN)SelectObject(hdc, colliderPen);
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));

        Ellipse(hdc, pos.x - collider, pos.y - collider, pos.x + collider, pos.y + collider);

        SelectObject(hdc, oldBrush);
        SelectObject(hdc, oldPen);
    }

    long PlayerProjectile::getTypeId()
    {
        return PlayerProjectile::TYPE_ID;
    }

    void PlayerProjectile::processCollisions(double dt)
    {
        if (!collisionBuffer.empty())
        {
            die();
        }
    }
}
