#ifndef AP_ABSTRACTFACTORY_H
#define AP_ABSTRACTFACTORY_H

#include "player.h"
#include "singletons.h"
#include "backgroundTile.h"

namespace world {
    class abstractFactory {
    protected:
        std::shared_ptr<world::rngFactory> rngFactory;
    public:
        virtual world::entity *produceEntity() = 0;

        virtual ~abstractFactory() = default;

        /*
        *
        * makes a player
        *
        * parameters:
        * x : x coordinate where the player should be spawned
        * y : y coordinate where the player shoudl be spawned
        * layer: the higher the layer, the later the sprite will be drawn
        * (so it will appear in front of something with a lower layer)
        * scale: scale by which the texture size should be multiplied
        *
        *
         * return: shared_ptr to the newly created player
        */
        virtual std::shared_ptr<world::player> producePlayer(float x, float y, int layer, float scale) = 0;

        /*
        *
        * produces platforms
        *
        * parameters:
        * estimatedHeight : height aroudn which platforms can spawn
        *   (currently can spawn up to a 100 units above or below this)
        * difficulty : number up to 5 which impacts what type of platforms will spawn
        * platforms: vector with all platforms to check if a new platform overlaps with another and if it's accessible
        *
        *
        * return: nothing, platforms are immediately put in the platforms vector
        */
        virtual void producePlatforms(int estimatedHeight, int difficulty,
                                      std::vector<std::shared_ptr<world::platform>> &platforms) = 0;

        /*
        *
        * makes a platform
        *
        * parameters:
        * x : x coordinate where the platform should be spawned
        * y : y coordinate where the platform shoudl be spawned
        * type: type of platform
        *
        * return: shared_ptr to the newly created platform
        */
        virtual std::shared_ptr<platform> producePlatform(int x, int y, platformType type) = 0;

        /*
        *
        * makes a bonus
        *
        * parameters:
        * x : x coordinate relative to the left of the platform it's on
        * bonusType : type of bonus
        *
        * return: shared_ptr to the newly created bonus
        */
        virtual std::shared_ptr<bonusItem> produceBonus(int x, bonusType) = 0;

        /*
        *
        * makes a background tile
        *
        * parameters:
        * x : x coordinate where the player should be spawned
        * y : y coordinate where the player shoudl be spawned
        *
        * return: shared_ptr to the newly created background tile
        */
        virtual std::shared_ptr<backgroundTile> produceBackgroundTile(int x, int y) = 0;
    };
}

#endif //AP_ABSTRACTFACTORY_H
