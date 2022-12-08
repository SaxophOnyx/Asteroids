#pragma once

#include "CollidableObject.h"
#include "IEventInput.h"
#include "CooldownTimer.h"

namespace ast
{
    class Player : public CollidableObject
    {
        public:
        static const long TYPE_ID = 2;

        Player(IEventInput& eventInput);
        Player(Player&) = delete;
        virtual ~Player();

        // Унаследовано через CollidableObject
        virtual void update(double dt) override;
        virtual void render(HDC hdc) override;
        virtual long getTypeId() override;

        double getAngle();
        void setAngle(double angle);

        private:
        const double ARROW_MULTIPLIER = 1.15f;
        const double TRAJECTORY_MULTIPLIER = 5.f;
        static HPEN colliderPen;
        static HPEN trajectoryPen;

        IEventInput& eventInput;
        double angle;
        CooldownTimer shootingTimer;
        int health;

        void handleRotationInput(double dt);
        void handleAccelerationInput(double dt);
        void handleShootingInput(double dt);
        void processCollisions(double dt);
    };
}
