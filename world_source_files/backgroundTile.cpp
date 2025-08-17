//
// Created by waffle_laptop on 16/08/2025.
//

#include "backgroundTile.h"

using namespace world;

backgroundTile::backgroundTile(int x, int y) : entity(x, y) {
    curHeight = -450;
}

int backgroundTile::getXCoord() const { return x; }

int backgroundTile::getYCoord() const { return y; }

void backgroundTile::newHeight(float newHeight) {
    if (y < newHeight - 450) {
        y += 925; // puts the background tile back at the top if it goes under the screen
    }
    curHeight = newHeight;
    positionCamera->updateCoords(x, y);
}