#pragma once

#include "EventBase.h"
#include "LargeAsteroid.h"

namespace ast
{
    class LargeAsteroidDestroyedEvent : public EventBase
    {
        public:
        static const long TYPE_ID = 3;
        
        LargeAsteroidDestroyedEvent(LargeAsteroid& asteroid, bool byPlayer);
        LargeAsteroidDestroyedEvent(LargeAsteroidDestroyedEvent&) = delete;
        virtual ~LargeAsteroidDestroyedEvent() = default;

        virtual long getTypeId() override;
        LargeAsteroid& getAsteroid();
        bool byPlayer();

        private:
        LargeAsteroid* asteroid;
        bool byPlayerFlag;
    };
}
