#pragma once

namespace ast
{
    class ICollidable
    {
        public:
        virtual ~ICollidable() = default;

        virtual bool collides(ICollidable& obj) = 0;

        protected:
        ICollidable() = default;
        ICollidable(ICollidable& obj) = delete;
    };
}
