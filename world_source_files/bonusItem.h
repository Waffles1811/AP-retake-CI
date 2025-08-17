//
// Created by waffle_laptop on 13/08/2025.
//

#ifndef AP_PROJECT_BONUSITEM_H
#define AP_PROJECT_BONUSITEM_H

#include <memory>
#include "entitycamera.h"

namespace world {
    enum bonusType {
        spring,
        jetpack,
        none
    };

    class bonusItem {
        std::shared_ptr<entitycamera> positionCamera;
        float x; // relative to the platform it's on
        bonusType typeBonus;
    public:
        bonusItem(float x, enum bonusType);

        ~bonusItem() = default;

        /*
        *
        * returns the type of this bonus
        *
        *
        * return: type of the bonus
        */
        enum bonusType getBonus() const;

        /*
        *
        * returns the x value (relative to the left of the platform it's on
        *
        * return: the x value
        */
        float getX() const;

        /*
        *
        * sets the position camera
        *
        * parameters: self-explanatory
        *
        */
        void setPCamera(std::shared_ptr<entitycamera>);

        /*
        *
        * moves the bonus and tells the position observer
        *
        * parameters:
        * platformX : x coordinate of the platform it's on
        * platformY : y coordinate of the platform it's on
        *
        */
        void timeUp(float platformX, float platformY);
    };
}

#endif //AP_PROJECT_BONUSITEM_H
