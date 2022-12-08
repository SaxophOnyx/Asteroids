#include "CooldownTimer.h"

namespace ast
{
    CooldownTimer::CooldownTimer(double cooldown)
        : cooldown(cooldown / 1000), remainingTime(cooldown / 1000)
    {

    }

    void CooldownTimer::update(double dt)
    {
        if (remainingTime <= dt)
            remainingTime = 0;
        else
            remainingTime -= dt;
    }

    void CooldownTimer::reset()
    {
        remainingTime = cooldown;
    }

    void CooldownTimer::setToZero()
    {
        remainingTime = 0;
    }

    bool CooldownTimer::isElapsed()
    {
        return remainingTime == 0;
    }
}
