#pragma once

#include <vector>
#include "State.h"
#include "Button.h"
#include "Player.h"
#include "CollisionSystem.h"
#include "SimpleObjectFactory.h"
#include "EventBus.h"
#include "LabeledCounter.h"
#include "CooldownTimer.h"
#include "LargeAsteroid.h"

namespace ast
{
    class GameState: public State
    {
        public:
        GameState(ISimpleResourceManager& resourceManager, RECT& windowBorders);
        GameState(GameState&) = delete;
        virtual ~GameState();

        virtual void update(double dt, POINT& mousePos) override;
        virtual void render(HDC hdc) override;

        private:
        Button* exitButton;
        LabeledCounter* scoreCounter;
        EventBus eventBus;
        SimpleObjectFactory objectFactory;
        CollisionSystem collisionSystem;
        std::vector<GameObject*> gameObjects;
        HBITMAP background;
        int asteroidsCount;
        int maxAsteroidCount;
        long playerScore;
        double playerTime;
        CooldownTimer asteroidSpawnTimer;

        void initGui();
        void initPlayer();
        void removeDeadObjects();
        void updateTimers(double dt);
        void processObjectEvents(double dt);
        void renderBackground(HDC hdc);
        void spawnAsteroid();
        void spawnPlayerProjectile(Player& player);
        void spawnLargeAsteroidShatters(LargeAsteroid& asteroid);
    };
}
