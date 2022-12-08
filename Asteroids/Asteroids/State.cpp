#include "State.h"

namespace ast
{
    State::State(ISimpleResourceManager& resourceManager, RECT& windowBorders)
        : resourceManager(resourceManager), windowBorders(windowBorders), newState(nullptr), isDeadFlag(false)
    {

    }

    bool State::isDead()
    {
        return this->isDeadFlag;
    }

    State* State::extractNewState()
    {
        State* result = this->newState;
        this->newState = nullptr;
        return result;
    }

    void State::die()
    {
        this->isDeadFlag = true;
    }

    void State::setNewState(State* newState)
    {
        this->newState = newState;
    }
}
