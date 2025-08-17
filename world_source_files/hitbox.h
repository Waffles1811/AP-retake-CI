#ifndef AP_HITBOX_H
#define AP_HITBOX_H

#include <iostream>

namespace world {
    class hitbox {// I might add hitboxes off different shapes later
    protected:
        float x;
        float y;
        float xOffset;
        float yOffset;
    public:
        hitbox(float _xOffset, float _yOffset);

        virtual ~hitbox() = default;

        /*
         *
         * sets the x coordinate of the left upper corner of the hitbox
         * parameters: self-explanatory
         *
         */
        virtual void setX(float _x);

        /*
         *
         * sets the y coordinate of the left upper corner of the hitbox
         * parameters: self-explanatory
         *
         */
        virtual void setY(float _y);
    };

    class rectHitbox : public hitbox {
    public:
        float length; // how far it stretches to the right from entity.x
        float height; // how far it stretches down from entity.y


        rectHitbox(float, float, float, float);

        ~rectHitbox() override = default;

        /*
         *
         * detects a collisions between two hitboxes
         * parameters:
         * otherBox: the other hitbox
         * oldY previous location of the hitbox to check if we went through it without detecting it
         *
         */
        bool detectCollision(rectHitbox &otherBox, float oldY) const;

        /*
         *
         * returns the x coordinate of the left side of the hitbox
         *
         * return: the x coordinate
         *
         */
        float getLeftX() const;

        /*
         *
         * returns the x coordinate of the right side of the hitbox
         *
         * return: the x coordinate
         *
         */
        float getRightX() const;

        /*
         *
         * returns the y coordinate of the upper side of the hitbox
         *
         * return: the y coordinate
         *
         */
        float getUpY() const;

        /*
         *
         * returns the y coordinate of the lower side of the hitbox
         *
         * return: the y coordinate
         *
         */
        float getDownY() const;
    };
}

#endif //AP_HITBOX_H
