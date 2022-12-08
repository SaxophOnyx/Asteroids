#include "LargeAsteroidDestroyedEvent.h"

namespace ast
{
    LargeAsteroidDestroyedEvent::LargeAsteroidDestroyedEvent(LargeAsteroid& asteroid, bool byPlayer)
        : asteroid(&asteroid), byPlayerFlag(byPlayer)
    {

    }

    long LargeAsteroidDestroyedEvent::getTypeId()
    {
        return LargeAsteroidDestroyedEvent::TYPE_ID;
    }

    LargeAsteroid& LargeAsteroidDestroyedEvent::getAsteroid()
    {
        return *asteroid;
    }

    bool LargeAsteroidDestroyedEvent::byPlayer()
    {
        return byPlayerFlag;
    }
}
