#pragma once

#include "EventBase.h"

namespace ast
{
    class IEventInput
    {
        public:
        IEventInput(IEventInput&) = delete;
        virtual ~IEventInput() = default;

        virtual void enque(EventBase* eventBase) = 0;

        protected:
        IEventInput() = default;
    };
}
