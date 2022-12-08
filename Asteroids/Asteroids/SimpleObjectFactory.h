#pragma once

#include <stack>
#include "IEventInput.h"
#include "ISimpleResourceManager.h"
#include "SmallAsteroid.h"
#include "PlayerProjectile.h"
#include "LargeAsteroid.h"

namespace ast
{
    class SimpleObjectFactory
    {
        public:
        SimpleObjectFactory(ISimpleResourceManager& resourceManager, IEventInput& eventInput);
        SimpleObjectFactory(SimpleObjectFactory&) = delete;
        virtual ~SimpleObjectFactory();

        SmallAsteroid* getSmallAsteroid();
        PlayerProjectile* getPlayerProjectile();
        LargeAsteroid* getLargeAsteroid();
        void saveOrDelete(GameObject* obj);

        private:
        IEventInput& eventInput;
        ISimpleResourceManager& resourceManager;
        std::stack<SmallAsteroid*> smallAsteroids;
        std::stack<PlayerProjectile*> playerProjectiles;
        std::stack<LargeAsteroid*> largeAsteroids;
    };
}
