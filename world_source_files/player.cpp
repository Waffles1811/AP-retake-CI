#include "player.h"
#include <cmath>
#include <iostream>
#include <utility>

enum playerPhysics { // divide things by 100.0 if they have "time" in their name bc no floats allowed
    jumpSpeed = 750,
    jumpingGravity = 800,
    downwardsGravity = 1200,
    walkSpeed = 400,
    walkAcceleration = 500,
    walkSlowdown = 1000,
    jetpackSpeed = 1000
};

world::player::player() : entity(0, 0) {
    hitbox = std::make_shared<world::rectHitbox>(77.74, 54, 0, 0);
    type = objectID::player;
}

world::player::player(float x, float y) : entity(x, y) {
    hitbox = std::make_shared<world::rectHitbox>(77.4, 54, 0, 0);
    type = objectID::player;
}

void world::player::initialize() {
    std::weak_ptr<player> this_pointer = shared_from_this();
    movement = std::make_shared<playerMovement>(this_pointer);
    inputHandling = std::make_shared<inputHandler>(movement);
    collisionFixer = std::make_shared<collisionHandler>(movement, this_pointer);
    animationHandling = std::make_shared<animationHandler>();
}

void world::player::timeUp(float time) {
    movement->timeUp(time);
    hitbox->setX(x);
    hitbox->setY(y);
}

void world::player::processInput(enum movement input) {
    inputHandling->processInput(input);
}

void world::player::handleCollision(const std::shared_ptr<platform> &hitObject) {
    collisionFixer->handleCollision(hitObject);
}

void world::player::setAnimationCameras(std::shared_ptr<world::animationObserver> _animobserver,
                                        std::shared_ptr<world::orientationObserver> _orientobserver) {
    animationHandling->setAnimationCameras(_animobserver, _orientobserver);
}

const std::shared_ptr<world::animationHandler> world::player::getAnimationHandling() const {
    return animationHandling;
}

void world::inputHandler::processInput(enum movement input) {
    switch (input) {
        case movement::moveRight:
            movement.lock()->goRight();
            break;
        case movement::moveLeft:
            movement.lock()->goLeft();
            break;
        case movement::stopRight:
            movement.lock()->stopRight();
        case movement::stopLeft:
            movement.lock()->stopLeft();
    }
}

world::inputHandler::inputHandler(std::weak_ptr<playerMovement> _movement) : movement(_movement) {}

void world::playerMovement::timeUp(float time) {
    if (ySpeed > 0) {  // grivity going up is lwoer because it makes the jump feel less airy
        ySpeed -= playerPhysics::jumpingGravity * time;
    } else {
        player_entity.lock()->getAnimationHandling()->processAnimation("fall");

        ySpeed -= playerPhysics::downwardsGravity * time;
    }
    if (goingLeft and xSpeed > -walkSpeed) {
        xSpeed -= walkAcceleration * time;
    } else if (goingRight and xSpeed < walkSpeed) {
        xSpeed += walkAcceleration * time;
    }
    if (not goingLeft and xSpeed < -5) {
        xSpeed += walkSlowdown * time;
    } else if (not goingRight and xSpeed > 5) {
        xSpeed -= walkSlowdown * time;
    } else if (xSpeed < 5 and xSpeed > -5) {
        xSpeed = 0;
    }
    player_entity.lock()->setCoords(player_entity.lock()->getXCoord() + time * xSpeed,
                                    player_entity.lock()->getYCoord() + time * ySpeed);

    if (jetpacktime > 0) {
        jetpacktime -= time;
        ySpeed = jetpackSpeed;
    }
}

void world::playerMovement::goLeft() {
    goingLeft = true;
    goingRight = false;
    player_entity.lock()->getAnimationHandling()->turn(true);
}

void world::playerMovement::goRight() {
    goingLeft = false;
    goingRight = true;
    player_entity.lock()->getAnimationHandling()->turn(false);
}

void world::playerMovement::stopLeft() {
    goingLeft = false;
}

void world::playerMovement::stopRight() {
    goingRight = false;
}

void world::playerMovement::jump() {
    ySpeed = jumpSpeed;
    player_entity.lock()->getAnimationHandling()->processAnimation("jump");
}

void world::playerMovement::land(float height) {
    player_entity.lock()->setYCoord(height + 57.5);
    ySpeed = 0;
    jump();
}

world::playerMovement::playerMovement(std::weak_ptr<player> _player_entity) : player_entity(_player_entity) {
    goingLeft = goingRight = false;
    xSpeed = ySpeed = 0.0;

}

void world::playerMovement::spring() {
    ySpeed = jumpSpeed * sqrt(5);
    player_entity.lock()->getAnimationHandling()->processAnimation("jump");
}

void world::playerMovement::jetpack() {
    jetpacktime = 2;
}

void world::collisionHandler::handleCollision(const std::shared_ptr<platform> &hitObject) {
    if (movement.lock()->ySpeed <= 0) {
        world::bonusType effect = hitObject->landedOn(player_entity.lock()->getXCoord());
        switch (effect) {
            case world::spring:
                // spring effect
                movement.lock()->spring();
                break;
            case world::jetpack:
                // jetpack effect
                movement.lock()->jetpack();
                break;
            default:
                movement.lock()->land(hitObject->getHitbox()->getUpY());
                break;
        }
    }
}

world::collisionHandler::collisionHandler(std::weak_ptr<playerMovement> _movement, std::weak_ptr<player> _player_entity
) : movement(std::move(_movement)),
    player_entity(std::move(_player_entity)) {}


void world::animationHandler::processAnimation(std::string animation) {
    observer->startAnimation(animation);
}

void world::animationHandler::setAnimationCameras(std::shared_ptr<world::animationObserver> _observer,
                                                  std::shared_ptr<world::orientationObserver> _obs) {
    observer = _observer;
    orientationObserver = _obs;
}

world::animationHandler::animationHandler() {}

void world::animationHandler::turn(bool direction) {
    orientationObserver->turn(direction);
}
