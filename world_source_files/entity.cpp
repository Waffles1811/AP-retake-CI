#include "entity.h"

#include <utility>

world::entity::entity(std::shared_ptr <world::rectHitbox> _hitbox, float _x, float _y)
        : hitbox(std::move(_hitbox)), x(_x), y(_y) {}

world::entity::entity(float _x, float _y) : x(_x), y(_y) {}

void world::entity::setpCam(std::shared_ptr <entitycamera> newCam) {
    positionCamera = std::move(newCam);
    positionCamera->updateCoords(x, y);
}

float world::entity::getXCoord() const {
    return x;
}

float world::entity::getYCoord() const {
    return y;
}

std::shared_ptr <world::rectHitbox> world::entity::getHitbox() {
    return hitbox;
}

void world::entity::setXCoord(float _x) {
    x = _x;
    if (positionCamera) {
        positionCamera->updateCoords(x, y);
    }
}

void world::entity::setYCoord(float _y) {
    y = _y;
    if (positionCamera) {
        positionCamera->updateCoords(x, y);
    }
}

void world::entity::setCoords(float _x, float _y) {
    x = _x;
    y = _y;
    if (positionCamera) {
        positionCamera->updateCoords(x, y);
    }
}

void world::entity::timeUp(float time) {}


