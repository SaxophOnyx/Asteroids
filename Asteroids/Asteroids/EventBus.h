#pragma once

#include <queue>
#include "IEventInput.h"

namespace ast
{
    class EventBus : public IEventInput
    {
        public:
        EventBus() = default;
        EventBus(EventBus&) = delete;
        virtual ~EventBus();

        virtual void enque(EventBase* newEvent) override;
        EventBase* deque();
        bool isEmpty();

        private:
        std::queue<EventBase*> events;
    };
}
