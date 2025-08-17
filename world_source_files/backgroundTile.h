//
// Created by waffle_laptop on 16/08/2025.
//

#ifndef AP_PROJECT_BACKGROUNDTILE_H
#define AP_PROJECT_BACKGROUNDTILE_H

#include "entity.h"

namespace world {
    class backgroundTile : public entity {
    protected:
        float curHeight;
    public:
        backgroundTile() = default;

        backgroundTile(int x, int y);

        ~backgroundTile() override = default;

        /*
         *
         * return: x_coord
         *
         */
        int getXCoord() const;

        /*
         *
         * return: Y_coord
         *
         */
        int getYCoord() const;

        /*
        *
        * changes height
        *
        * parameters:
        * newHeight: the newHeight
        *
        */
        void newHeight(float newHeight);
    };
} // namespace dj

#endif //AP_PROJECT_BACKGROUNDTILE_H
