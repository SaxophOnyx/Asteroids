#pragma once

#include <stack>
#include <queue>
#include "State.h"
#include "GameState.h"

namespace ast
{
    class StateMachine
    {
        public:
        StateMachine() = default;
        StateMachine(StateMachine&) = delete;
        virtual ~StateMachine() = default;

        void update(double dt, POINT& mousePos);
        void render(HDC hdc);

        State& peek();
        State* pop();
        void push(State* state);
        bool isEmpty();

        private:
        std::stack<State*> states;
    };
}
