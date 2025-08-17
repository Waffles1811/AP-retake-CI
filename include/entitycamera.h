#ifndef LITTLEGAME_ENTITYCAMERA_H
#define LITTLEGAME_ENTITYCAMERA_H

#include <map>
#include <string>

namespace world {
    class entitycamera {
    public:
        entitycamera() = default;

        virtual ~entitycamera() = default;

        /*
         *
         * makes the viewEntity update the coordinates
         *
         * parameters: self-explanatory
         *
         */
        virtual void updateCoords(float _x, float _y) = 0;
    };

    class animationObserver {
    public:
        animationObserver() = default;

        virtual ~animationObserver() = default;

        /*
         *
         * tells the viewEntity to start an animation
         *
         * parameters:
         * anim: name of the animation
         *
         */
        virtual void startAnimation(std::string anim) = 0;

        /*
         *
         * tells the viewEntity to stop the animation and return to the default sprite
         *
         *
         *
         */
        virtual void stopAnimation() = 0;
    };

    class orientationObserver {
        /* left = true, right = false */
    public:
        orientationObserver() = default;

        virtual ~orientationObserver() = default;

        /*
         *
         * tell the viewEntity to turn the sprite around
         *
         */
        virtual void turn(bool direction) = 0;
    };

    class scoreObserver {
    public:
        scoreObserver() = default;

        virtual ~scoreObserver() = default;

        /*
         *
         * tells the view class to update the score (score from height is not included in this)
         *
         * parameters:
         * increase: amount with which the score has gone up (can also eb negative if the score went down)
         *
         */
        virtual void updateScore(int increase) = 0;

        /*
         *
         * updates the height (highest point the top of the player has reached) for the view class
         *
         * parameters:
         * amount: the absolute value of the height
         *
         */
        virtual void updateHeight(float amount) = 0;

        /*
         *
         * resets the score and height
         *
         */
        virtual void reset() = 0;
    };
}

#endif //LITTLEGAME_ENTITYCAMERA_H
