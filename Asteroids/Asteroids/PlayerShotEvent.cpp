#include "PlayerShotEvent.h"
#include "Player.h"

namespace ast
{
    PlayerShotEvent::PlayerShotEvent(Player& player)
        : EventBase(), player(&player)
    {

    }

    long PlayerShotEvent::getTypeId()
    {
        return PlayerShotEvent::TYPE_ID;
    }

    Player& PlayerShotEvent::getPlayer()
    {
        return *player;
    }
}
