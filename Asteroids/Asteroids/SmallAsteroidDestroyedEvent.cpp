#include "SmallAsteroidDestroyedEvent.h"

namespace ast
{
    SmallAsteroidDestroyedEvent::SmallAsteroidDestroyedEvent(SmallAsteroid& asteroid, bool byPlayer)
        : asteroid(&asteroid), byPlayerFlag(byPlayer)
    {

    }

    long SmallAsteroidDestroyedEvent::getTypeId()
    {
        return SmallAsteroidDestroyedEvent::TYPE_ID;
    }

    SmallAsteroid& SmallAsteroidDestroyedEvent::getAsteroid()
    {
        return *asteroid;
    }

    bool SmallAsteroidDestroyedEvent::byPlayer()
    {
        return byPlayerFlag;
    }
}
