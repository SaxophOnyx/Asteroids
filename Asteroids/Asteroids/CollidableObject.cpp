#include "CollidableObject.h"

namespace ast
{
    CollidableObject::CollidableObject(double collider)
        : collider(collider)
    {

    }

    CollidableObject::~CollidableObject()
    {

    }

    double CollidableObject::getCollider()
    {
        return collider;
    }

    bool CollidableObject::collides(CollidableObject& obj)
    {
        return pos.distance(obj.pos) < collider + obj.collider;
    }

    bool CollidableObject::isOutside(RECT& boundaries)
    {
        double left = pos.x - collider;
        double right = pos.x + collider;
        double top = pos.y - collider;
        double bottom = pos.y + collider;

        return !(right > boundaries.left
            && left < boundaries.right
            && bottom > boundaries.top
            && top < boundaries.bottom);
    }

    void CollidableObject::registerCollision(CollidableObject& obj)
    {
        collisionBuffer.push(&obj);
    }
}
