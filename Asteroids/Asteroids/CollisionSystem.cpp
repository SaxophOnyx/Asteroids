#include "CollisionSystem.h"

namespace ast
{
    CollisionSystem::CollisionSystem(RECT& borders)
        : borders(borders)
    {

    }

    void CollisionSystem::addObject(CollidableObject& obj)
    {
        this->objects.push_back(&obj);
    }

    void CollisionSystem::update(double dt)
    {
        this->updateCollisions(dt);
        //this->removeDeadObjects();
    }

    void CollisionSystem::updateCollisions(double dt)
    {
        for (int i = 0; i < objects.size(); ++i)
        {
            CollidableObject* a = objects.at(i);

            if (shouldBeTransfered(*a))
                transferObjectFromOutOfBounds(*a);

            for (int j = i + 1; j < objects.size(); ++j)
            {
                CollidableObject* b = objects.at(j);

                if (a->collides(*b))
                {
                    a->registerCollision(*b);
                    b->registerCollision(*a);
                }
            }
        }
    }

    void CollisionSystem::removeDeadObjects()
    {
        int i = 0;
        int currSize = objects.size();
        while (i < currSize)
        {
            if (objects.at(i)->isDead())
            {
                objects.at(i) = objects.at(currSize - 1);
                objects.pop_back();
                --currSize;
            }
            else
                ++i;
        }
    }

    bool CollisionSystem::shouldBeTransfered(CollidableObject& obj)
    {
        return obj.isOutside(borders);
    }

    void CollisionSystem::transferObjectFromOutOfBounds(CollidableObject& obj)
    {
        auto& vel = obj.getVelocity();
        if (vel.x == 0)
        {
            transferVertically(obj);
            return;
        }

        if (vel.y == 0)
        {
            transferHorizontally(obj);
            return;
        }

        auto& pos = obj.getPosition();
        Point a, b; //прямая, вдоль которой движется объект
        a.x = pos.x;
        a.y = pos.y;
        b.x = a.x + vel.x;
        b.y = a.y + vel.y;

        double bx; //вертикальная сторона огранич. прямоугольника
        if (pos.x > borders.right)
            bx = borders.left;
        else
            bx = borders.right;

        double by; //горизонтальная сторонв огранич. прямоугольника
        if (pos.y > borders.bottom)
            by = borders.top;
        else
            by = borders.bottom;

        Point vert; //точка перемечения прямой движения объекта и вертикальной стороны огранич. прямоугольника
        vert.x = bx;
        vert.y = ((vert.x - a.x) * (b.y - a.y)) / (b.x - a.x) + a.y;

        Point horiz; //точка перемечения прямой движения объекта и горизонтальной стороны огранич. прямоугольника
        horiz.y = by;
        horiz.x = ((horiz.y - a.y) * (b.x - a.x)) / (b.y - a.y) + a.x;

        if (pos.distance(vert) < pos.distance(horiz))
        {
            if (pos.x > vert.x)
            {
                double newPosX = vert.x - obj.getCollider() + 1;
                double newPosY = ((newPosX - a.x) * (b.y - a.y) / (b.x - a.x)) + a.y;
                obj.setPosition(newPosX, newPosY);
            }
            else
            {
                double newPosX = vert.x + obj.getCollider() - 1;
                double newPosY = ((newPosX - a.x) * (b.y - a.y) / (b.x - a.x)) + a.y;
                obj.setPosition(newPosX, newPosY);
            }
        }
        else
        {
            if (pos.y > horiz.y)
            {
                double newPosY = horiz.y - obj.getCollider() + 1;
                double newPosX = ((newPosY - a.y) * (b.x - a.x) / (b.y - a.y)) + a.x;
                obj.setPosition(newPosX, newPosY);
            }
            else
            {
                double newPosY = horiz.y + obj.getCollider() - 1;
                double newPosX = ((newPosY - a.y) * (b.x - a.x) / (b.y - a.y)) + a.x;
                obj.setPosition(newPosX, newPosY);
            }
        }
    }

    void CollisionSystem::transferHorizontally(CollidableObject& obj)
    {
        auto& pos = obj.getPosition();
        if (pos.x > borders.right)
        {
            obj.setPosition(borders.left - obj.getCollider() + 1, pos.y);
        }
        else
        {
            obj.setPosition(borders.right + obj.getCollider() - 1, pos.y);
        }
    }


    void CollisionSystem::transferVertically(CollidableObject& obj)
    {
        auto& pos = obj.getPosition();
        if (pos.y > borders.bottom)
        {
            obj.setPosition(pos.x, borders.top - obj.getCollider() + 1);
        }
        else
        {
            obj.setPosition(pos.x, borders.bottom + obj.getCollider() - 1);
        }
    }
}
