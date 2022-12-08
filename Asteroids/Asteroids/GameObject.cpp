#include "GameObject.h"

namespace ast
{
    GameObject::GameObject()
        : isDeadFlag(false), pos(0.f, 0.f)
    {

    }

    bool GameObject::isDead()
    {
        return this->isDeadFlag;
    }

    const Point& GameObject::getPosition()
    {
        return pos;
    }

    const Vector2& GameObject::getVelocity()
    {
        return velocity;
    }

    void GameObject::setPosition(double x, double y)
    {
        pos.x = x;
        pos.y = y;
    }

    void GameObject::setPosition(const Point& position)
    {
        pos.x = position.x;
        pos.y = position.y;
    }

    void GameObject::setVelocity(double x, double y)
    {
        velocity.x = x;
        velocity.y = y;
    }

    void GameObject::setVelocity(const Vector2& velocity)
    {
        this->velocity.x = velocity.x;
        this->velocity.y = velocity.y;
    }

    void GameObject::die()
    {
        this->isDeadFlag = true;
    }
}
