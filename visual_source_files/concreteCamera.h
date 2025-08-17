#ifndef AP_CONCRETECAMERA_H
#define AP_CONCRETECAMERA_H

#include "../include/entitycamera.h"
#include "../include/entity.h"
#include "view.h"

namespace world {
    class entitycamera;  // Forward declaration
}

namespace repr {
    class concreteCamera : public world::entitycamera {
        std::shared_ptr<viewEntity> model;
    public:
        concreteCamera(std::shared_ptr<viewEntity>);

        ~concreteCamera() override = default;

        /*
         *
         * makes the viewEntity update the coordinates
         *
         * parameters: self-explanatory
         *
         */
        void updateCoords(float _x, float _y) override;
    };

    class concreteAnimationObserver : public world::animationObserver {
    private:
        std::string curAnimation;
        std::shared_ptr<viewEntity> model;
    public:
        concreteAnimationObserver(std::shared_ptr<viewEntity>);

        ~concreteAnimationObserver() override = default;

        /*
         *
         * tells the viewEntity to start an animation
         *
         * parameters:
         * anim: name of the animation
         *
         */
        void startAnimation(std::string anim) override;

        /*
         *
         * tells the viewEntity to stop the animation and return to the default sprite
         *
         *
         *
         */
        void stopAnimation() override;
    };

    class concreteOrientationObserver : public world::orientationObserver {
    private:
        bool facingLeft;
        std::shared_ptr<viewEntity> model;
    public:
        concreteOrientationObserver(std::shared_ptr<viewEntity>);

        ~concreteOrientationObserver() override = default;

        /*
         *
         * tell the viewEntity to turn the sprite around
         *
         *
         *
         */
        void turn(bool direction) override;
    };

    class concreteScoreObserver : public world::scoreObserver {
    private:
        std::shared_ptr<view> playerView;
        int score;
        float height;
    public:
        concreteScoreObserver(std::shared_ptr<view>);

        ~concreteScoreObserver() override = default;

        /*
         *
         * tells the view class to update the score (score from height is not included in this)
         *
         * parameters:
         * increase: amount with which the score has gone up (can also eb negative if the score went down)
         *
         */
        void updateScore(int increase) override;

        /*
         *
         * updates the height (highest point the top of the player has reached) for the view class
         *
         * parameters:
         * amount: the absolute value of the height
         *
         */
        void updateHeight(float amount) override;

        /*
         *
         * resets the score and height
         *
         */
        void reset() override;
    };
}

#endif //AP_CONCRETECAMERA_H
