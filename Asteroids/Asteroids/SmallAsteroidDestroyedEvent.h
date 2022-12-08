#pragma once

#include "EventBase.h"
#include "SmallAsteroid.h"

namespace ast
{
    class SmallAsteroidDestroyedEvent : public EventBase
    {
        public:
        static const long TYPE_ID = 2;

        SmallAsteroidDestroyedEvent(SmallAsteroid& asteroid, bool byPlayer);
        SmallAsteroidDestroyedEvent(SmallAsteroidDestroyedEvent&) = delete;
        virtual ~SmallAsteroidDestroyedEvent() = default;

        virtual long getTypeId() override;
        SmallAsteroid& getAsteroid();
        bool byPlayer();

        private:
        SmallAsteroid* asteroid;
        bool byPlayerFlag;
    };
}
