#include "AsteroidBase.h"

namespace ast
{
    AsteroidBase::AsteroidBase(IEventInput& eventInput, double collider)
        : CollidableObject(collider), eventInput(eventInput)
    {

    }
}
