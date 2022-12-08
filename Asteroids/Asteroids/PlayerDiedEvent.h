#pragma once

#include "EventBase.h"
#include "Player.h"

namespace ast
{
    class PlayerDiedEvent : public EventBase
    {
        public:
        static const long TYPE_ID = 1;

        PlayerDiedEvent(Player& player);
        PlayerDiedEvent(PlayerDiedEvent&) = delete;
        virtual ~PlayerDiedEvent() = default;

        virtual long getTypeId() override;
        Player& getPlayer();

        private:

        Player& player;
    };
}
