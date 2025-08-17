#ifndef AP_OBJECT_H
#define AP_OBJECT_H

#include "entity.h"
#include "bonusItem.h"

namespace world {
    enum platformType {
        stationary,
        horizontallyMoving,
        verticallyMoving,
        disappearing
    };

    class platform : public entity {
    protected:
        std::shared_ptr<world::animationObserver> theAnimationObserver;
        std::shared_ptr<bonusItem> bonus;
        bool jumpedOn;
        enum platformType type;
    public:
        platform(float x, float y, std::shared_ptr<bonusItem> _bonus);

        ~platform() override = default;

        /*
         *
         * tells the platform it was landed on and returns what the bonus of the platform was
         *
         * parameters:
         * x: x coordinate of the player character
         *
         * return: type of the bonus (spring, jetpack or none)
         *
         */
        virtual bonusType landedOn(float x);

        /*
         * sets the animation camera
         */
        void setAnimationCamera(std::shared_ptr<world::animationObserver>);


        /*
         *
         * returns the offset for moving platforms
         *
         * return: the offset
         *
         */
        virtual float getOffset() const;

        /*
         *
         * returns whether or not this platform has already been jumped on
         *
         * return: true if the player already jumped on this, false if not
         *
         */
        bool getIsJumpedOn() const;

        /*
         *
         * returns the type of the platform
         *
         * return: the type of the platform
         *
         */
        platformType getType() const;

        /*
         *
         * times up the platform, tells the position camera to update the position
         *
         * parameters:
         * time: how much time has passed
         *
         */
        void timeUp(float) override;

        /*
         *
         * sets the bonus for this platform
         *
         * parameters:
         * _bonus: the new bonus
         *
         */
        void setBonus(std::shared_ptr<bonusItem>);

        /*
         *
         * check if this platform is still on the platform
         *
         * parameters:
         * height: the height, middle of the screen which is 900 pixels big
         *
         * return: true if it is, false if it's not
         *
         */
        virtual bool checkOnScreen(float height) const;
    };

    class stationaryPlatform : public platform {
    public:
        stationaryPlatform(float x, float y, std::shared_ptr<bonusItem> _bonus);
    };

    class horizontalPlatform : public platform {
    private:
        float offset;
        bool goingLeft;
        float speed;
    public:
        horizontalPlatform(float x, float y, float speed, std::shared_ptr<bonusItem> _bonus);

        ~horizontalPlatform() override = default;

        /*
         *
         * returns the offset
         *
         * return: the offset
         *
         */
        float getOffset() const override;

        /*
         *
         * moves the platform and tells the position observer
         *
         * parameters:
         * time: how much time has passed since the last frame
         *
         */
        void timeUp(float time) override;
    };

    class verticalPlatform : public platform {
    private:
        float offset;
        bool goingUp;
        float speed;
    public:
        verticalPlatform(float x, float y, float speed, std::shared_ptr<bonusItem> _bonus);

        ~verticalPlatform() override = default;

        /*
         *
         * returns the offset
         *
         * return: the offset
         *
         */
        float getOffset() const override;

        /*
         *
         * moves the platform and updates the position camera
         *
         * parameters:
         * time: how much time has passed since last frame
         */
        void timeUp(float time) override;

        /*
         *
         * checks if this platform is still on the screen take into account that the platform can still go up
         *
         * return: true if it's on the screen, false if it's off screen
         *
         */
        bool checkOnScreen(float height) const override;
    };

    class disappearingPlatform : public platform {
        float disappearingTime;
        bool isDisappearing;
    public:
        disappearingPlatform(float x, float y, std::shared_ptr<bonusItem> _bonus);

        ~disappearingPlatform() override = default;

        /*
         * checks if disappearing ,if so counts down, if under zero it disappears
         */
        void timeUp(float time);

        /*
         *
         * moves the platform down so world will despawn it, also checks if a bonus was hit
         *
         * parameters:
         * x: the x coordinate of the player that landed on this platform
         *
         * return: the type of bonus that was hit
         *
         */
        bonusType landedOn(float x) override;
    };

}

#endif //AP_OBJECT_H
