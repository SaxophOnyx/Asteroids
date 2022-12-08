#pragma once

#include "Windows.h"
#include "Point.h"
#include "Vector2.h"

namespace ast
{
    class GameObject
    {
        public:
        virtual ~GameObject() = default;

        virtual void update(double dt) = 0;
        virtual void render(HDC hdc) = 0;
        virtual long getTypeId() = 0;

        bool isDead();
        const Point& getPosition();
        const Vector2& getVelocity();
        void setPosition(double x, double y);
        void setPosition(const Point& position);
        void setVelocity(double x, double y);
        void setVelocity(const Vector2& velocity);

        protected:
        GameObject();
        GameObject(GameObject&) = delete;
        
        void die();

        Point pos;
        Vector2 velocity;

        private:
        bool isDeadFlag;
    };
}
