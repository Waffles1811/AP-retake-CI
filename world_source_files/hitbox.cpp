#include "hitbox.h"

void world::hitbox::setX(float _x) {
    x = _x + xOffset;
}

void world::hitbox::setY(float _y) {
    y = _y + yOffset;
}

world::hitbox::hitbox(float _xOffset, float _yOffset) : x(0), y(0), xOffset(_xOffset), yOffset(_yOffset) {}

world::rectHitbox::rectHitbox(float _length, float _height, float _x_offset, float _y_offset)
        : hitbox(_x_offset, _y_offset), length(_length), height(_height) {}

bool world::rectHitbox::detectCollision(world::rectHitbox &otherBox, float yDif) const {
    if (otherBox.getLeftX() < getRightX() and otherBox.getRightX() > getLeftX()) {
        if (otherBox.getUpY() > getDownY() and
            ((otherBox.getUpY() < getDownY() - yDif) or otherBox.getDownY() < getDownY())) {
            return true;
        }
    }
    return false;
}

float world::rectHitbox::getLeftX() const {
    return x;
}

float world::rectHitbox::getRightX() const {
    return x + length;
}

float world::rectHitbox::getUpY() const {
    return y;
}

float world::rectHitbox::getDownY() const {
    return y - height;
}