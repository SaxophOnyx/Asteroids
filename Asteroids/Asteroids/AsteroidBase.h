#pragma once

#include "CollidableObject.h"
#include "IEventInput.h"
#include "Point.h"
#include "Vector2.h"

namespace ast
{
    class AsteroidBase : public CollidableObject
    {
        public:
        AsteroidBase(AsteroidBase&) = delete;
        virtual ~AsteroidBase() = default;

        protected:
        AsteroidBase(IEventInput& eventInput, double collider);

        IEventInput& eventInput;
    };
}
