#pragma once

#include <vector>
#include "CollidableObject.h"

namespace ast
{
    class CollisionSystem
    {
        public:
        CollisionSystem(RECT& borders);
        CollisionSystem(CollisionSystem&) = delete;
        virtual ~CollisionSystem() = default;

        void addObject(CollidableObject& obj);
        void update(double dt);
        void removeDeadObjects();

        private:
        RECT& borders;
        std::vector<CollidableObject*> objects;

        void updateCollisions(double dt);
        bool shouldBeTransfered(CollidableObject& obj);

        void transferObjectFromOutOfBounds(CollidableObject& obj);
        void transferHorizontally(CollidableObject& obj);
        void transferVertically(CollidableObject& obj);
    };
}
