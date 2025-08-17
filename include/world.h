#ifndef AP_WORLD_H
#define AP_WORLD_H

#include "abstractFactory.h"
#include "thread"
#include <cmath>

namespace world {
    class world {
    protected:
        float height;
        std::unique_ptr<scoreObserver> scoreKeeper;
        std::shared_ptr<player> playerchar;
        std::shared_ptr<abstractFactory> factory;
        std::vector<std::shared_ptr<platform>> platforms;
        std::vector<std::shared_ptr<backgroundTile>> bgTiles;
        int difficulty;
        float lastPlatforms;

    public:
        world(std::shared_ptr<abstractFactory>, std::unique_ptr<scoreObserver>);

        ~world() = default;

        /*
         *
         * set up the world, calls the function which spawns the background, the player, and some platforms
         *
         */
        void setup();

        /*
         *
         * separate from the rest of the setup function so it can be a serperate thread (this take a while)
         *
         */
        void setupBackground();

        /*
         *
         * calls the time up functions for the players etc. checks if the player is till on screen
         * checks if platforms are still on screen and deletes them if not, checks if the height needs updating
         * handles the difficulty, spawns in new platforms
         *
         * parameters:
         * time: how much time has passed since the last frame
         *
         */
        bool time_up(float time);

        /*
         *
         * passes the inputs to the player
         *
         */
        void processInputs(movement);

        /*
         *
         * resets the world, deletes all platforms, the player etc.
         *
         */
        void reset();
    };
}

#endif //AP_WORLD_H
