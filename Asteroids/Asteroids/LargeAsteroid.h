#pragma once

#include "AsteroidBase.h"
#include "IEventInput.h"

namespace ast
{
    class SmallAsteroid;
    class Player;
    class PlayerProjectile;

    class LargeAsteroid : public AsteroidBase
    {
        public:
        static const long TYPE_ID = 3;

        LargeAsteroid(IEventInput& eventInput);
        LargeAsteroid(LargeAsteroid&) = delete;
        virtual ~LargeAsteroid() = default;

        virtual void update(double dt) override;
        virtual void render(HDC hdc) override;
        virtual long getTypeId() override;
        int getDamage();

        private:
        static HPEN colliderPen;

        void processCollisions(double dt);
        void collideWithSmallAsteroid(double dt, SmallAsteroid& asteroid);
        void collideWithLargeAsteroid(double dt, LargeAsteroid& asteroid);
        void collideWithPlayerProjectile(double dt, PlayerProjectile& proj);
        void collideWithPlayer(double dt, Player& player);
    };
}
