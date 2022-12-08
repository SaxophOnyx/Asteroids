#include "StateMachine.h"

namespace ast
{
    void StateMachine::update(double dt, POINT& mousePos)
    {
        if (!this->isEmpty())
        {
            State* top = states.top();
            State* newState = top->extractNewState();

            if (top->isDead())
            {
                states.pop();
                delete(top);
            }

            if (newState != nullptr)
                states.push(newState);

            if (!states.empty())
                states.top()->update(dt, mousePos);
        }
    }

    void StateMachine::render(HDC hdc)
    {
        if (!this->isEmpty())
        {
            this->peek().render(hdc);
        }
    }

    State& StateMachine::peek()
    {
        return *this->states.top();
    }

    State* StateMachine::pop()
    {
        State* tmp = this->states.top();
        this->states.pop();
        return tmp;
    }

    void StateMachine::push(State* state)
    {
        this->states.push(state);
    }

    bool StateMachine::isEmpty()
    {
        return this->states.empty();
    }
}
