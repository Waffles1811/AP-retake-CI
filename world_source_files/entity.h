#ifndef AP_ENTITY_H
#define AP_ENTITY_H

#include <memory>
#include <vector>
#include <string>
#include "../json.hpp"
#include "entitycamera.h"
#include "hitbox.h"

using json = nlohmann::json;

class saveFileObject;

enum objectID : int32_t {
    player,
};

namespace world {
    class entity {
    protected:
        float x;
        float y;
        objectID type;
        std::shared_ptr<entitycamera> positionCamera;
        std::shared_ptr<world::rectHitbox> hitbox;

    public:
        entity(std::shared_ptr<world::rectHitbox> _hitbox, float _x, float _y);

        entity(float _x, float _y);

        virtual ~entity() = default;

        /*
        *
        * returns the x coordinate of the entity
        *
        * return: the x coordinate of this
        *
        */
        float getXCoord() const;

        /*
        *
        * returns the y coordinate of the entity
        *
        * return: the y coordinate of this
        *
        */
        float getYCoord() const;

        /*
        *
        * sets the x coordinate of the entity
        *
        * parameters: self-explanatory
        */
        void setXCoord(float _x);

        /*
        *
        * sets the y coordinate of the entity
        *
        * parameters: self-explanatory
        */
        void setYCoord(float _y);

        /*
        *
        * sets both the x and y coordinates of the entity
        *
        * parameters:
        * x: new x coordinate
        * y: the new y coordinate
        */
        void setCoords(float, float);

        /*
        *
        * return the hitbox
        *
        * return: shared pointer to the hitbox
        */
        std::shared_ptr<world::rectHitbox> getHitbox();

        /*
        *
        * sets the position camera (observer) of the entity
        *
        * parameters: self-explanatory
        */
        void setpCam(std::shared_ptr<entitycamera> newCam);

        /*
        *
        * doesn't do anything, just here so derived classes can override this
        *
        * parameters:
        * time: how much time passed since last frame
        */
        virtual void timeUp(float time);
    };
}


#endif //AP_ENTITY_H
