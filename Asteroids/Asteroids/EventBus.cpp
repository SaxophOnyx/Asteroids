#include "EventBus.h"

namespace ast
{
    EventBus::~EventBus()
    {
        while (!events.empty())
        {
            delete(events.front());
            events.pop();
        }
    }

    void EventBus::enque(EventBase* newEvent)
    {
        events.push(newEvent);
    }

    EventBase* EventBus::deque()
    {
        EventBase* e = events.front();
        events.pop();
        return e;
    }

    bool EventBus::isEmpty()
    {
        return events.empty();
    }
}
