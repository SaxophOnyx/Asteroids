#pragma once

#include <Windows.h>
#include "ISimpleResourceManager.h"

namespace ast
{
    class State
    {
        public:
        State(State&) = delete;
        virtual ~State() = default;

        virtual void update(double dt, POINT& mousePos) = 0;
        virtual void render(HDC hdc) = 0;

        bool isDead();
        State* extractNewState();

        protected:
        ISimpleResourceManager& resourceManager;
        RECT& windowBorders;

        State(ISimpleResourceManager& resourceManager, RECT& windowBorders);
        void die();
        void setNewState(State* newState);

        private:
        bool isDeadFlag;
        State* newState;
    };
}
