#pragma once

namespace ast
{
    class CooldownTimer
    {
        public:
        CooldownTimer(double cooldown);
        CooldownTimer(CooldownTimer&) = delete;
        virtual ~CooldownTimer() = default;

        void update(double dt);
        void reset();
        void setToZero();
        bool isElapsed();

        private:
        double cooldown;
        double remainingTime;
    };
}
