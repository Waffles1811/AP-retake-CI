#include "platform.h"

world::platform::platform(float x, float y, std::shared_ptr<bonusItem> _bonus) : entity(x, y) {
    bonus = _bonus;
    hitbox = std::make_shared<world::rectHitbox>(115, 25, 0, 0); //25
    hitbox->setX(x);
    hitbox->setY(y);
    jumpedOn = false;
    theAnimationObserver = nullptr;
}

world::bonusType world::platform::landedOn(float playerX) {
    jumpedOn = true;
    if (bonus) {
        if ((x + bonus->getX() < playerX and x + bonus->getX() + 50 > playerX) or
            (playerX < x + bonus->getX() and x + bonus->getX() < playerX + 46) or
            (playerX < x + bonus->getX() and x + bonus->getX() + 50 < playerX + 46)) {
            return bonus->getBonus();
        }
    }
    return bonusType::none;
}


void world::platform::setAnimationCamera(std::shared_ptr<world::animationObserver> obs) {
    theAnimationObserver = obs;
}

world::platformType world::platform::getType() const {
    return type;
}

float world::platform::getOffset() const {
    return 0;
}

void world::platform::timeUp(float time) {
    if (bonus) {
        bonus->timeUp(x, y);
    }
}

void world::platform::setBonus(std::shared_ptr<bonusItem> _bonus) {
    bonus = _bonus;
}

bool world::platform::getIsJumpedOn() const {
    return jumpedOn;
}

bool world::platform::checkOnScreen(float height) const {
    if (height - 550 > y) {
        return false;
    }
    return true;
}


world::stationaryPlatform::stationaryPlatform(float x, float y, std::shared_ptr<bonusItem> _bonus)
        : platform(x, y, _bonus) {
    type = stationary;
}

world::horizontalPlatform::horizontalPlatform(float x, float y, float _speed, std::shared_ptr<bonusItem> _bonus)
        : platform(x, y, _bonus), speed(_speed), offset(0), goingLeft(true) {
    type = horizontallyMoving;

}


void world::horizontalPlatform::timeUp(float time) {
    if (goingLeft) {
        if (offset < -100) { // turn around if to far left
            goingLeft = false;
            offset += time * speed;
        } else {
            offset -= time * speed;
        }
    } else {
        if (offset > 100) {  // turn around if to far right
            goingLeft = true;
            offset -= time * speed;
        } else {
            offset += time * speed;
        }
    }
    positionCamera->updateCoords(x + offset, y);
    if (bonus) {
        bonus->timeUp(x + offset, y);
    }
    hitbox->setX(x + offset);
}

float world::horizontalPlatform::getOffset() const {
    return offset;
}

world::verticalPlatform::verticalPlatform(float x, float y, float _speed, std::shared_ptr<bonusItem> _bonus)
        : platform(x, y, _bonus), speed(_speed), offset(0), goingUp(true) {
    type = verticallyMoving;
}

float world::verticalPlatform::getOffset() const {
    return offset;
}

void world::verticalPlatform::timeUp(float time) {
    if (goingUp) {
        if (offset < -100) { // changes direction if too far down
            goingUp = false;
            offset += time * speed;
        } else {
            offset -= time * speed;
        }
    } else {
        if (offset > 100) { // changes direction if too far up
            goingUp = true;
            offset -= time * speed;
        } else {
            offset += time * speed;
        }
    }
    positionCamera->updateCoords(x, y + offset);
    if (bonus) {
        bonus->timeUp(x, y + offset);
    }
    hitbox->setY(y + offset);
}

bool world::verticalPlatform::checkOnScreen(float height) const {
    if (height - 660 > y) {
        return false;
    }
    return true;
}

world::disappearingPlatform::disappearingPlatform(float x, float y, std::shared_ptr<bonusItem> _bonus)
        : platform(x, y, _bonus) , disappearingTime(0.45), isDisappearing(false) {
    type = disappearing;
}

world::bonusType world::disappearingPlatform::landedOn(float playerX) {
    isDisappearing  = true;
    theAnimationObserver->startAnimation("disappear");
    if (bonus) {
        if ((x + bonus->getX() < playerX and x + bonus->getX() + 50 > playerX) or
            // checks if player touched the power up
            (playerX < x + bonus->getX() and x + bonus->getX() < playerX + 46) or
            (playerX < x + bonus->getX() and x + bonus->getX() + 50 < playerX + 46)) {
            return bonus->getBonus();
        }
    }
    bonus = nullptr;
    return bonusType::none;
}


void world::disappearingPlatform::timeUp(float time) {
    if (bonus) {
        bonus->timeUp(x, y);
    }
    if (isDisappearing){
        if (disappearingTime < 0){
            y = -2000;
        } else {
            disappearingTime -= time;
        }
    }
}

