//
// Created by waffle_laptop on 13/08/2025.
//

#include "bonusItem.h"


world::bonusItem::bonusItem(float _x, world::bonusType type) : x(_x), typeBonus(type) {}

world::bonusType world::bonusItem::getBonus() const {
    return typeBonus;
}

float world::bonusItem::getX() const {
    return x;
}

void world::bonusItem::timeUp(float platformX, float platformY) {
    if (typeBonus == world::spring) {
        positionCamera->updateCoords(platformX + x, platformY + 90);
        // has to be higher because otherwise its in the platform
    } else {
        positionCamera->updateCoords(platformX + x, platformY + 55);

    }
}

void world::bonusItem::setPCamera(std::shared_ptr<entitycamera> cam) {
    positionCamera = cam;
}
