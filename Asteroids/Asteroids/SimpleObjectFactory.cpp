#include "SimpleObjectFactory.h"

namespace ast
{
    SimpleObjectFactory::SimpleObjectFactory(ISimpleResourceManager& resourceManager, IEventInput& eventInput)
        : resourceManager(resourceManager), eventInput(eventInput)
    {

    }

    SimpleObjectFactory::~SimpleObjectFactory()
    {
        while (!smallAsteroids.empty())
        {
            delete(smallAsteroids.top());
            smallAsteroids.pop();
        }

        while (!playerProjectiles.empty())
        {
            delete(playerProjectiles.top());
            playerProjectiles.pop();
        }
    }

    SmallAsteroid* SimpleObjectFactory::getSmallAsteroid()
    {
        if (smallAsteroids.empty())
        {
            SmallAsteroid* res = new SmallAsteroid(eventInput);
            return res;
        }
        else
        {
            SmallAsteroid* res = smallAsteroids.top();
            smallAsteroids.pop();
            return res;
        }
    }

    PlayerProjectile* SimpleObjectFactory::getPlayerProjectile()
    {
        if (playerProjectiles.empty())
        {
            PlayerProjectile* res = new PlayerProjectile();
            return res;
        }
        else
        {
            PlayerProjectile* res = playerProjectiles.top();
            playerProjectiles.pop();
            return res;
        }
    }

    LargeAsteroid* SimpleObjectFactory::getLargeAsteroid()
    {
        if (largeAsteroids.empty())
        {
            LargeAsteroid* asteroid = new LargeAsteroid(eventInput);
            return asteroid;
        }
        else
        {
            LargeAsteroid* asteroid = largeAsteroids.top();
            largeAsteroids.pop();
            return asteroid;
        }
    }

    void SimpleObjectFactory::saveOrDelete(GameObject* obj)
    {
        long id = obj->getTypeId();
        switch (id)
        {
            case SmallAsteroid::TYPE_ID:
                smallAsteroids.push(static_cast<SmallAsteroid*>(obj));
                break;

            case PlayerProjectile::TYPE_ID:
                playerProjectiles.push(static_cast<PlayerProjectile*>(obj));
                break;

            case LargeAsteroid::TYPE_ID:
                largeAsteroids.push(static_cast<LargeAsteroid*>(obj));
                break;

            default:
                delete(obj);
                break;
        }
    }
}
