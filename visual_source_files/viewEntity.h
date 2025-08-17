#ifndef AP_VIEWENTITY_H
#define AP_VIEWENTITY_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "../json.hpp"

using json = nlohmann::json;

#include "animationLibrary.h"

namespace repr {
    class animationHandler;

    class viewEntity : public std::enable_shared_from_this<viewEntity> {
    protected:
        float x;
        float y;
        std::shared_ptr<sf::Texture> texture;
        std::shared_ptr<sf::Sprite> sprite;
        std::unique_ptr<repr::animationHandler> animationHandling;
        sf::IntRect spriteRect;
        std::string type;
        std::string folder;
        float scale;
        int leftXOffset; // sometime animations need us to add an offset since the left top corner might change
        int rightXOffset;
        int yOffset;
        bool curDirection;
    public:
        viewEntity(std::string &_type, std::string &folder, float _scale, std::shared_ptr<sf::Texture> _texture);

        ~viewEntity() = default;

        /*
        *
        * sets up animation handler
        *
        *
        */
        void initialiseAnimations(std::shared_ptr<animationLibrary> _library);

        /*
        *
        * progresses the animation, moves the sprite into the correct position and then returns it.
        *
        * parameters:
        * time : how much time passed since last frame
        * height: how high up the screen is
        *
        */
        sf::Sprite getSprite(float time, float height);

        /*
        *
        * updates the texture box (for animations generally)
        *
        */
        void setTextureBox(int newX, int newY);

        /*
        *
        * sets texture
        *
        * parameters:
         * _etxture: the new texture
         * newLength: the length of the texture box put over the texture
         * newHeight: the height of the texture box put over the texture
        */
        void setTexture(std::string &_texture, float newLength, float newHeight);

        /*
        *
        * sets offsets
        *
        * parameters: self explanatory
        *
        */
        void setOffsets(int leftXOffset, int rightXOffset, int yOffset);

        /*
        *
        * returns to the default texture
        *
        */
        void defaultTexture();

        /*
        *
        * updates the position of what were presenting
        *
        * parameters: self-explanatory
        *
        */
        void updatePosition(float newX, float NewY);

        /*
        *
        * make the sprite turn around
        *
        */
        void changeOrientation();

        /*
        *
        * tells the animation handler to start a new animation
        *
        * parameters:
        * anim: name of the animation
        *
        */
        void startAnimation(std::string anim);
    };

    class animationHandler {
    private:
        std::string type;
        std::shared_ptr<animationLibrary> library;
        json animation_data;
        std::weak_ptr<viewEntity> sprite;
        std::vector<float> frameDurations; // in milliseconds
        std::string curAnimation;
        float timeSinceLastFrame;
        int curFrame;
        int curX; // where in the sprite sheet we are now
        int curY;
        int xOffset; // how many pixels we have to move for next sprite
        bool inAnimation;
        bool repeatingAnimation;
    public:
        animationHandler(std::string &_type, const std::shared_ptr<viewEntity>,
                         std::shared_ptr<animationLibrary> _library);

        ~animationHandler() = default;

        /*
        *
        * update animation, calls function to progress the animation or end it
        *
        * parameters:
        * time : how much time passed since last frame
        *
        */
        void updateAnimation(float time);

        /*
        *
        * starts a new animation
        *
        * parameters:
        * type : name of the animation we want to start
        *
        */
        void startAnimation(std::string type);

        /*
        *
        * progresses the animation
        *
        * parameters:
        * time : how muh time has passed since last frame
        *
        */
        void continueAnimation(float time);

        /*
        *
        * stops an animation and goes back to the default texture
        *
        *
        */
        void stopAnimation();
    };
} // repr

#endif //AP_VIEWENTITY_H
