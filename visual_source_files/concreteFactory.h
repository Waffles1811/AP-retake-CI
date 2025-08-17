#ifndef AP_CONCRETEFACTORY_H
#define AP_CONCRETEFACTORY_H

#include "../include/abstractFactory.h"
#include "view.h"
#include "../include//world.h"
#include "concreteCamera.h"

namespace repr {
    class concreteFactory : public world::abstractFactory {
        std::shared_ptr<repr::view> playerView;
        std::shared_ptr<animationLibrary> library;
        std::unordered_map<std::string, sf::Texture> defaultTextures; // decreases loading time
    public:
        concreteFactory(std::shared_ptr<repr::view>);

        ~concreteFactory() override = default;

        world::entity *produceEntity() override; // doesn't do anything

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
        std::shared_ptr<world::player> producePlayer(float x, float y, int layer, float scale) override;

        /*
        *
        * calculates coordinates for where to spawn a new platform
        * it will try to find coordinates which don't overlap with another platform and are accessible
        * but if it can't find one it will settle for a position which is just accessible
        *
        * parameters:
        * estHeight : estimated height of where tha platform should go
        *      platforms can be spawned 100 units above or below this
        * type : type of platform
        * platforms: vector off all other platforms so we can check if they overlap/if it's accessible
        *
        *
        * return: the x and y coordinates that were found
        */
        std::pair<int, int> calcCoordinates(int estHeight, world::platformType type,
                                            const std::vector<std::shared_ptr<world::platform>> &platforms) const;

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
        void producePlatforms(int estimatedHeight, int difficulty,
                              std::vector<std::shared_ptr<world::platform>> &platforms) override;

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
        std::shared_ptr<world::platform> producePlatform(int x, int y, world::platformType type) override;

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
        std::shared_ptr<world::bonusItem> produceBonus(int x, world::bonusType) override;

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
        std::shared_ptr<world::backgroundTile> produceBackgroundTile(int x, int y) override;

    };
}

#endif //AP_CONCRETEFACTORY_H
