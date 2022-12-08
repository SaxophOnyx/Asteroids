#pragma once

#include "AsteroidBase.h"
#include <wincrypt.h>

namespace ast
{
    class LargeAsteroid;
    class Player;
    class PlayerProjectile;

    class SmallAsteroid : public AsteroidBase
    {
        public:
        static const long TYPE_ID = 1;

        SmallAsteroid(IEventInput& eventInput);
        SmallAsteroid(SmallAsteroid&) = delete;
        virtual ~SmallAsteroid() = default;

        virtual void update(double dt) override;
        virtual void render(HDC hdc) override;
        virtual long getTypeId() override;
        int getDamage();

        private:
        static HPEN colliderPen;

        void processCollisions(double dt);
        void collideWithSmallAsteroid(double dt, SmallAsteroid& a);
        void collideWithLargeAsteroid(double dt, LargeAsteroid& a);
        void collideWithPlayerProjectile(double dt, PlayerProjectile& p);
        void collideWithPlayer(double dt, Player& p);
    };
}
