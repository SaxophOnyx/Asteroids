#pragma once

namespace ast
{
    class EventBase
    {
        public:
        EventBase(EventBase&) = delete;
        virtual ~EventBase() = default;

        virtual long getTypeId() = 0;

        protected:
        EventBase() = default;
    };
}
