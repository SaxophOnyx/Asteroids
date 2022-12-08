#pragma once

#include "EventBase.h"

namespace ast
{
    class Player;

    class PlayerShotEvent : public EventBase
    {
        public:
        static const long TYPE_ID = 4;

        PlayerShotEvent(Player& player);
        PlayerShotEvent(PlayerShotEvent&) = delete;
        virtual ~PlayerShotEvent() = default;

        virtual long getTypeId() override;
        Player& getPlayer();

        private:
        Player* player;
    };
}
