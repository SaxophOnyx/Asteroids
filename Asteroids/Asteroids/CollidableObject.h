#pragma once

#include <queue>
#include "GameObject.h"

namespace ast
{
    class CollidableObject : public GameObject
    {
        public:
        CollidableObject(CollidableObject&) = delete;
        virtual ~CollidableObject();
        
        double getCollider();
        virtual bool collides(CollidableObject& obj);
        virtual bool isOutside(RECT& boundaries);
        void registerCollision(CollidableObject& obj);

        protected:
        CollidableObject(double collider);
        double collider;
        std::queue<CollidableObject*> collisionBuffer;
    };
}
