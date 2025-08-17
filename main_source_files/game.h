#ifndef AP_GAME_H
#define AP_GAME_H

#include <fstream>
#include "../include/singletons.h"
#include "../visual_source_files/concreteFactory.h"

class game {
protected:
    std::unique_ptr<world::world> world;
    std::shared_ptr<repr::view> playerView;
    std::unique_ptr<world::stopwatchFactory> stopwatchInc;
public:
    game();

    ~game() = default;

    /*
     *
     * tells the world class to set up the game
     *
     *
     *
     */
    void setup();


    /*
     *
     * hosts the main game loop, let's the world time up
     *
     */
    void mainGameLoop();


    /*
     *
     * checks if there were inputs and passes them on to the world
     *
     *
     */
    void processInputs();

    /*
     *
     * tells the world class and view class to go in gameOver mode and waits untill r is pressed
     * if r is pressed it will setup again and then go back to the main game loop
     *
     *
     */
    void gameOver();
};


#endif //AP_GAME_H
