#pragma once

#include "CollidableObject.h"

namespace ast
{
    class PlayerProjectile : public CollidableObject
    {
        public:
        static const long TYPE_ID = 4;

        PlayerProjectile();
        PlayerProjectile(PlayerProjectile&) = delete;
        virtual ~PlayerProjectile() = default;;

        virtual void update(double dt) override;
        virtual void render(HDC hdc) override;
        virtual long getTypeId() override;

        private:
        static HPEN colliderPen;

        void processCollisions(double dt);
    };
}
