#ifndef AP_VIEW_H
#define AP_VIEW_H

#include "memory"
#include <map>
#include <fstream>
#include "viewEntity.h"

namespace repr {
    class view {
        std::vector<std::vector<std::weak_ptr<viewEntity>>> entities;
        int score;
        float height;
        sf::Font font;
    public:
        std::unique_ptr<sf::RenderWindow> window;

        view();

        ~view() = default;

        /*
        *
        * adds an entity to it's vector
        *
        * parameters:
        * entity : the new viewEntity
        * layer: layer where it should go (higher layer -> more to the front)
        *
        */
        void addEntity(std::shared_ptr<viewEntity>, int layer);

        /*
        *
        * makes a frame and puts it on the screen
        *
        * parameters:
        * time : how much time ahs passed (used for animations)
        *
        */
        void makeFrame(float time);


        /*
        *
        * resets everything
        *
        */
        void reset();

        /*
        *
        * update the score
        *
        * parameters:
        * amount : relative amount by which the score has goen up (can be negative if score went down)
        * ( doesn't include the score derived from height)
        *
        */
        void updateScore(int amount);

        /*
        *
        * update the height
        *
        * parameters:
        * amount : absolute value of the height
        *
        */
        void updateHeight(float amount);

        /*
        *
        * draws the score on the screen
        *
        * parameters:
        * score : score (including the height)
        *
        */
        void drawScore(int score);

        /*
        *
        * draws the game over screen and updates the highscore.txt file
        *
        *
        */
        void drawGameOverScreen();
    };
}

#endif //AP_VIEW_H
