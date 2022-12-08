#include "PlayerDiedEvent.h"

namespace ast
{
    PlayerDiedEvent::PlayerDiedEvent(Player& player)
        : EventBase(), player(player)
    {

    }

    long PlayerDiedEvent::getTypeId()
    {
        return TYPE_ID;
    }

    Player& PlayerDiedEvent::getPlayer()
    {
        return player;
    }
}
