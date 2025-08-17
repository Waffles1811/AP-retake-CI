#ifndef AP_PLAYER_H
#define AP_PLAYER_H

#include "platform.h"

enum class movement {
    moveRight,
    moveLeft,
    stopLeft,
    stopRight
};

namespace world {
    // some declarations
    class playerMovement;

    class inputHandler;

    class collisionHandler;

    class animationHandler;

    class player : public entity, public std::enable_shared_from_this<player> {
    private:
        std::shared_ptr<playerMovement> movement;
        std::shared_ptr<inputHandler> inputHandling;
        std::shared_ptr<collisionHandler> collisionFixer;
        std::shared_ptr<animationHandler> animationHandling;
    public:
        player();

        player(float x, float y);

        ~player() override = default;

        /*
         *
         * initializes the player, sets up the movement class etc.
         *
         *
         */
        void initialize();

        /*
         *
         * moves up the platform, applies the speed, applies gravity, applies the jetpack effect if relevant
         * let's you move left and right
         *
         * parameters:
         * time: how much time has passed since teh last frame
         *
         */
        void timeUp(float time) override;

        /*
         *
         * receives an input and passes it to the input ahndler
         *
         * parameters:
         * input: what input was received
         *
         */
        void processInput(enum movement input);

        /*
         *
         * handles a collision, will jump or maye apply a bonus effect
         *
         * parameters:
         * hitObject: the platform that was hit
         *
         */
        void handleCollision(const std::shared_ptr<platform> &hitObject);

        /*
         *
         * passes the animation and orientation camera to the animation handler
         *
         * parameters: self-explanatory, should be in shared pointer containers
         *
         */
        void setAnimationCameras(std::shared_ptr<world::animationObserver> _animobserver,
                                 std::shared_ptr<world::orientationObserver> _orientobserver);

        /*
         *
         * returns the animation handling
         *
         * return: the animation handling
         *
         */
        const std::shared_ptr<animationHandler> getAnimationHandling() const;
    };

    class inputHandler {
        std::weak_ptr<playerMovement> movement;
    public:
        inputHandler(std::weak_ptr<playerMovement>);

        ~inputHandler() = default;

        /*
         *
         * calls the relevant functions based on what input was received
         *
         * parameters:
         * input: what input was received
         *
         */
        void processInput(enum movement input);
    };

    class playerMovement {
    public:
        float xSpeed;
        float ySpeed;
        std::weak_ptr<player> player_entity;
        bool goingLeft;
        bool goingRight;
        float jetpacktime;

        playerMovement(std::weak_ptr<player>);

        ~playerMovement() = default;

        /*
         *
         * moves up the platform, applies the speed, applies gravity, applies the jetpack effect if relevant
         * let's you move left and right
         *
         * parameters:
         * time: how much time has passed since teh last frame
         *
         */
        void timeUp(float time);

        /*
         *
         * let the player go left
         *
         *
         */
        void goLeft();

        /*
         *
         * let the player go right
         *
         */
        void goRight();

        /*
         *
         * stop the person from going left
         *
         */
        void stopLeft();

        /*
         *
         * stop the person from going right
         *
         */
        void stopRight();

        /*
         *
         * land on a platform
         *
         * parameters:
         * height: the y coordinate of the platform the player landed on
         *
         */
        void land(float height);

        /*
         *
         * let the player jump
         *
         */
        void jump();

        /*
         *
         * let the player jump very high
         *
         */
        void spring();

        /*
         *
         * let the player fly up
         *
         */
        void jetpack();
    };

    class collisionHandler {
        std::weak_ptr<playerMovement> movement;
        std::weak_ptr<player> player_entity;
    public:
        ~collisionHandler() = default;

        collisionHandler(std::weak_ptr<playerMovement>, std::weak_ptr<player>);

        /*
         *
         * handles a collision, checks if there is a bonus and then calls the relevant function
         *
         * parameters:
         * hitObject: the platform of what was hit
         *
         */
        void handleCollision(const std::shared_ptr<platform> &hitObject);
    };

    class animationHandler { // maybe change the hitbox in certain scenarios idk
        std::shared_ptr<world::animationObserver> observer;
        std::shared_ptr<world::orientationObserver> orientationObserver;
    public:
        animationHandler();

        ~animationHandler() = default;

        /*
         *
         * tells the observer to start an animation
         *
         * parameters:
         * animationID: what animation we should start
         *
         */
        void processAnimation(std::string animationID);

        /*
         *
         * sets up the cameras
         *
         * parameters: self-explanatory
         *
         */
        void setAnimationCameras(std::shared_ptr<world::animationObserver> _animobserver,
                                 std::shared_ptr<world::orientationObserver> _orientobserver);

        /*
         *
         * tells the observer that the player turned around
         *
         */
        void turn(bool direction);
    };
}

#endif //AP_PLAYER_H
