#include "concreteFactory.h"

#include <utility>


repr::concreteFactory::concreteFactory(std::shared_ptr<repr::view> _playerView) : playerView(std::move(_playerView)) {
    library = std::make_shared<animationLibrary>(animationLibrary("assets/player"));
    library->readFolder("assets/tempPlatform");
    sf::Texture texture;
    if (!texture.loadFromFile("assets/bgTile/bgTile_default.png")) {
        throw std::runtime_error("backgroundTile texture file failed to load.\nPlease ensure"
                                 " assets/bgTile/bgTile_default.png is present");
    }
    defaultTextures["bgTile"] = texture;
    if (!texture.loadFromFile("assets/horizontalPlatform/horizontalPlatform_default.png")) {
        throw std::runtime_error("backgroundTile texture file failed to load.\nPlease ensure"
                                 " assets/horizontalPlatform/horizontalPlatform_default.png is present");
    }
    defaultTextures["horizontalPlatform"] = texture;
    if (!texture.loadFromFile("assets/jetpack/jetpack_default.png")) {
        throw std::runtime_error("backgroundTile texture file failed to load.\nPlease ensure"
                                 " assets/jetpack/jetpack_default.png is present");
    }
    defaultTextures["jetpack"] = texture;
    if (!texture.loadFromFile("assets/player/player_default.png")) {
        throw std::runtime_error("backgroundTile texture file failed to load.\nPlease ensure"
                                 " assets/player/player_default.png is present");
    }
    defaultTextures["player"] = texture;
    if (!texture.loadFromFile("assets/spring/spring_default.png")) {
        throw std::runtime_error("backgroundTile texture file failed to load.\nPlease ensure"
                                 " assets/spring/spring_default.png is present");
    }
    defaultTextures["spring"] = texture;
    if (!texture.loadFromFile("assets/staticPlatform/staticPlatform_default.png")) {
        throw std::runtime_error("backgroundTile texture file failed to load.\nPlease ensure"
                                 " assets/staticPlatform/staticPlatform_default.png is present");
    }
    defaultTextures["staticPlatform"] = texture;
    if (!texture.loadFromFile("assets/tempPlatform/tempPlatform_default.png")) {
        throw std::runtime_error("backgroundTile texture file failed to load.\nPlease ensure"
                                 " assets/tempPlatform/tempPlatform_default.png is present");
    }
    defaultTextures["tempPlatform"] = texture;
    if (!texture.loadFromFile("assets/verticalPlatform/verticalPlatform_default.png")) {
        throw std::runtime_error("backgroundTile texture file failed to load.\nPlease ensure"
                                 " assets/verticalPlatform/verticalPlatform_default.png is present");
    }
    defaultTextures["verticalPlatform"] = texture;

}

world::entity *repr::concreteFactory::produceEntity() {
    // produce X fun tions are generally structured like:
    // make the model
    // make the cameras
    // make the actual thing we're making
    // add entity to playerView
    // return the actual thing that was made
    return nullptr;
}

std::shared_ptr<world::player> repr::concreteFactory::producePlayer(float x, float y, int layer, float scale) {
    std::string name = "player";
    std::shared_ptr<repr::viewEntity> model = std::make_shared<repr::viewEntity>(name, name,
                                                                                 scale, std::make_shared<sf::Texture>(
                    defaultTextures[name]));
    model->initialiseAnimations(library);
    std::shared_ptr<repr::concreteCamera> cam = std::make_shared<repr::concreteCamera>(model);
    std::shared_ptr<repr::concreteAnimationObserver> obs =
            std::make_shared<repr::concreteAnimationObserver>(model);
    std::shared_ptr<repr::concreteOrientationObserver> orobs =
            std::make_shared<repr::concreteOrientationObserver>(model);
    std::shared_ptr<world::player> player = std::make_shared<world::player>(world::player(x, y));
    player->initialize();
    player->setpCam(cam);
    player->setAnimationCameras(obs, orobs);
    playerView->addEntity(model, layer);
    return player;
}


std::pair<int, int> repr::concreteFactory::calcCoordinates(int estheight, world::platformType type,
                                                           const std::vector<std::shared_ptr<world::platform>> &platforms) const {
    // the player can go around 450 pixels to the left or right for the height of the heighest possible platform
    bool found_coordinates = false;
    bool accessible = true;
    int index = 0;
    int x_coord;
    int y_coord;
    while (!((accessible and found_coordinates) or (index > 100 and accessible))) {
        // if we haven't found a coordinate which doesn't overlap with another platform after 100 tries
        // we kinda give up and just go for an accessible one
        index++;
        accessible = false;
        found_coordinates = true;
        x_coord = rngFactory->getRNG()->generateRandomint(0, 584);
        y_coord = estheight + rngFactory->getRNG()->generateRandomint(-100, 100);
        int travelDistance;
        if (y_coord < 0) {
            travelDistance = 450; // about how far you can get
        } else {
            travelDistance = 350;
        }
        // how it works:
        //
        // 1. check if they overlap with basic rectangle overlaps
        // 2. check if they're accessible by checking if they are father than 450/350 units away (takes how far they move into account)
        // looks like it would take a while but is suprisingly performant bh
        switch (type) {
            case world::platformType::horizontallyMoving:
                for (const auto &i: platforms) {
                    if (i->getType() == world::stationary or i->getType() == world::disappearing) {
                        if (((i->getXCoord() + 115.2 > x_coord - 100 and i->getXCoord() + 115.2 < x_coord + 215.2) or
                             x_coord - 100 < i->getXCoord() and x_coord + 215.2 > i->getXCoord()) and
                            ((i->getYCoord() > y_coord - 36.0 and i->getYCoord() - 36.0 < y_coord) or
                             y_coord > i->getYCoord() - 36 and y_coord - 36 < i->getYCoord())) { // do they overlap
                            found_coordinates = false;
                            break;
                        }

                        if ((x_coord < i->getXCoord() and i->getXCoord() - (x_coord + 215) > travelDistance) or
                            (x_coord > i->getXCoord() and
                             (x_coord - 100) - i->getXCoord() + 115.2)) { // can they be accessed
                            accessible = true;
                        }
                    }
                    if (i->getType() == world::horizontallyMoving) {
                        if (((i->getXCoord() + 15.2 > x_coord - 100 and i->getXCoord() + 215.2 < x_coord + 215.2) or
                             x_coord - 100 < i->getXCoord() - 100 and x_coord + 215.2 > i->getXCoord() - 100) and
                            ((i->getYCoord() > y_coord - 36.0 and i->getYCoord() - 36.0 < y_coord) or
                             y_coord > i->getYCoord() - 36 and y_coord - 36 < i->getYCoord())) {
                            found_coordinates = false;
                            break;
                        }

                        if ((x_coord < i->getXCoord() and (i->getXCoord()) - (x_coord + 215) > travelDistance) or
                            (x_coord > i->getXCoord() and (x_coord - 100) - i->getXCoord() + 115.2)) {
                            accessible = true;
                        }
                    }

                    if (i->getType() == world::verticallyMoving) {
                        if (((i->getXCoord() + 15.2 > x_coord - 100 and i->getXCoord() + 215.2 < x_coord + 215.2) or
                             x_coord - 100 < i->getXCoord() - 100 and x_coord + 215.2 > i->getXCoord() - 100) and
                            ((y_coord < i->getYCoord() + 100 and y_coord > i->getYCoord() - 136) or
                             (y_coord - 36 < i->getYCoord() + 100 and y_coord - 36 > i->getYCoord() - 136))) {
                            found_coordinates = false;
                            break;
                        }

                        if ((x_coord < i->getXCoord() and (i->getXCoord()) - (x_coord + 215) > travelDistance) or
                            (x_coord > i->getXCoord() and (x_coord - 100) - i->getXCoord() + 115.2)) {
                            accessible = true;
                        }
                    }
                }
                break;

            case world::platformType::verticallyMoving:
                for (const auto &i: platforms) {
                    if (i->getType() == world::stationary or i->getType() == world::disappearing) {
                        if (((i->getXCoord() + 115.2 > x_coord and i->getXCoord() + 115.2 < x_coord + 115.2) or
                             x_coord < i->getXCoord() and x_coord + 115.2 > i->getXCoord()) and
                            ((i->getYCoord() > y_coord - 136.0 and i->getYCoord() - 36.0 < y_coord + 100) or
                             y_coord + 100 > i->getYCoord() - 36 and y_coord - 136 < i->getYCoord())) {
                            found_coordinates = false;
                            break;
                        }

                        if ((x_coord < i->getXCoord() and (i->getXCoord()) - (x_coord + 115) > travelDistance) or
                            (x_coord > i->getXCoord() and (x_coord) - i->getXCoord() + 115.2)) {
                            accessible = true;
                        }

                    } else if (i->getType() == world::horizontallyMoving) {
                        if (((i->getXCoord() + 115.2 > x_coord - 100 and i->getXCoord() + 115.2 < x_coord + 215.2) or
                             x_coord - 100 < i->getXCoord() and x_coord + 215.2 > i->getXCoord()) and
                            ((i->getYCoord() > y_coord - 136.0 and i->getYCoord() - 36.0 < y_coord + 100) or
                             y_coord + 100 > i->getYCoord() - 136 and y_coord - 136 < i->getYCoord())) {
                            found_coordinates = false;
                            break;
                        }

                        if ((x_coord < i->getXCoord() and (i->getXCoord()) - (x_coord + 115) > travelDistance) or
                            (x_coord > i->getXCoord() and (x_coord) - i->getXCoord() + 115.2)) {
                            accessible = true;
                        }
                    }

                    if (i->getType() == world::verticallyMoving) {
                        if (((i->getXCoord() + 115.2 > x_coord and i->getXCoord() + 115.2 < x_coord + 115.2) or
                             x_coord < i->getXCoord() and x_coord + 115.2 > i->getXCoord()) and
                            ((i->getYCoord() + 100 > y_coord - 136.0 and i->getYCoord() - 136.0 < y_coord + 100) or
                             y_coord + 100 > i->getYCoord() - 136 and y_coord - 136 < i->getYCoord() + 100)) {
                            found_coordinates = false;
                            break;
                        }
                    }

                    if ((x_coord < i->getXCoord() and (i->getXCoord()) - (x_coord + 115) > travelDistance) or
                        (x_coord > i->getXCoord() and (x_coord) - i->getXCoord() + 115.2)) {
                        accessible = true;
                    }
                }

                break;

            default:
                for (const auto &i: platforms) {
                    if (i->getType() == world::stationary or i->getType() == world::disappearing) {
                        if (((i->getXCoord() + 115.2 > x_coord and i->getXCoord() + 115.2 < x_coord + 115.2) or
                             x_coord < i->getXCoord() and x_coord + 115.2 > i->getXCoord()) and
                            ((i->getYCoord() > y_coord - 36.0 and i->getYCoord() - 36.0 < y_coord) or
                             y_coord > i->getYCoord() - 36 and y_coord - 36 < i->getYCoord())) {
                            found_coordinates = false;
                            break;
                        }

                        if ((x_coord < i->getXCoord() and (i->getXCoord()) - (x_coord + 115) > travelDistance) or
                            (x_coord > i->getXCoord() and (x_coord) - i->getXCoord() + 115.2)) {
                            accessible = true;
                        }
                    }
                    if (i->getType() == world::horizontallyMoving) {
                        if (((i->getXCoord() + 215.2 > x_coord and i->getXCoord() + 215.2 < x_coord + 115.2) or
                             x_coord < i->getXCoord() - 100 and x_coord + 115.2 > i->getXCoord() - 100) and
                            ((i->getYCoord() > y_coord - 36.0 and i->getYCoord() - 36.0 < y_coord) or
                             y_coord > i->getYCoord() - 36 and y_coord - 36 < i->getYCoord())) {
                            found_coordinates = false;
                            break;
                        }

                        if ((x_coord < i->getXCoord() and (i->getXCoord() - 100) - (x_coord + 115) > travelDistance) or
                            (x_coord > i->getXCoord() and (x_coord) - i->getXCoord() + 215.2)) {
                            accessible = true;
                        }
                    }
                    if (i->getType() == world::verticallyMoving) {
                        if (((i->getXCoord() + 115.2 > x_coord and i->getXCoord() + 115.2 < x_coord + 115.2) or
                             x_coord < i->getXCoord() and x_coord + 115.2 > i->getXCoord()) and
                            ((i->getYCoord() + 100 > y_coord - 36.0 and i->getYCoord() - 136.0 < y_coord) or
                             y_coord > i->getYCoord() - 136 and y_coord - 36 < i->getYCoord() + 100)) {
                            found_coordinates = false;
                            break;
                        }
                    }

                    if ((x_coord < i->getXCoord() and (i->getXCoord() - 100) - (x_coord + 115) > travelDistance) or
                        (x_coord > i->getXCoord() and (x_coord) - i->getXCoord() + 215.2)) {
                        accessible = true;
                    }
                }
                break;
        }
    }
    return {x_coord, y_coord};
}

void repr::concreteFactory::producePlatforms(int estimatedHeight, int difficulty,
                                             std::vector<std::shared_ptr<world::platform>> &platforms) {
    int maxAmountOfPlatforms;
    switch (difficulty) {
        case 1:
            maxAmountOfPlatforms = 3;
            break;
        case 2:
            maxAmountOfPlatforms = 3;
            break;
        case 3:
            maxAmountOfPlatforms = 2;
            break;
        case 4:
            maxAmountOfPlatforms = 2;
            break;
        default:
            maxAmountOfPlatforms = 1;
            break;
    }
    int amount =
            rngFactory->getRNG()->generateRandomint(std::max(1, maxAmountOfPlatforms - 1), maxAmountOfPlatforms + 1);
    for (int i = 0; i < amount; i++) {
        world::platformType type;

        int typeRandom = rngFactory->getRNG()->generateRandomint(1, 21);
        switch (difficulty) {
            case 1:
                if (typeRandom < 15) { // 70%
                    type = world::stationary;
                } else if (typeRandom == 15) { // 5%
                    type = world::horizontallyMoving;
                } else if (typeRandom == 16) { // 5%
                    type = world::verticallyMoving;
                } else { // 20%
                    type = world::disappearing;
                }
                break;

            case 2:
                if (typeRandom < 13) { // 60%
                    type = world::stationary;
                } else if (typeRandom < 15) { // 10%
                    type = world::horizontallyMoving;
                } else if (typeRandom < 17) { // 10%
                    type = world::verticallyMoving;
                } else { // 20%
                    type = world::disappearing;
                }
                break;

            case 3:
                if (typeRandom < 7) { // 30%
                    type = world::stationary;
                } else if (typeRandom < 11) { // 20%
                    type = world::horizontallyMoving;
                } else if (typeRandom < 15) { // 20%
                    type = world::verticallyMoving;
                } else { // 30%
                    type = world::disappearing;
                }
                break;

            case 4:
                if (typeRandom < 3) { // 10%
                    type = world::stationary;
                } else if (typeRandom < 9) { // 30%
                    type = world::horizontallyMoving;
                } else if (typeRandom < 15) { // 30%
                    type = world::verticallyMoving;
                } else { // 30%
                    type = world::disappearing;
                }
                break;
            default:
            case 5:
                if (typeRandom == 1) { // 5%
                    type = world::stationary;
                } else if (typeRandom < 9) { // 35%
                    type = world::horizontallyMoving;
                } else if (typeRandom < 15) { // 30%
                    type = world::verticallyMoving;
                } else { // 30%
                    type = world::disappearing;
                }
                break;
        }
        std::pair<int, int> coords = calcCoordinates(estimatedHeight, type, platforms);
        platforms.push_back(producePlatform(coords.first, coords.second, type));
        int bonusRandom = rngFactory->getRNG()->generateRandomint(0, 75);
        switch (bonusRandom) {
            case 1:
            case 2:
                platforms.back()->setBonus(produceBonus(rngFactory->getRNG()->generateRandomint(0, 50),
                                                        world::bonusType::spring));
                break;
            case 3:
                platforms.back()->setBonus(produceBonus(rngFactory->getRNG()->generateRandomint(0, 50),
                                                        world::bonusType::jetpack));
                break;
            default:
                platforms.back()->setBonus(nullptr);
                break;
        }
    }
}

std::shared_ptr<world::platform>
repr::concreteFactory::producePlatform(int x, int y, world::platformType type) {
    std::shared_ptr<repr::viewEntity> model;
    std::shared_ptr<world::platform> newPlatform;
    std::string name;
    float speed;
    switch (type) {
        case world::platformType::stationary:
            name = "staticPlatform";
            model = std::make_shared<repr::viewEntity>(name, name, 7.2,
                                                       std::make_shared<sf::Texture>(defaultTextures[name]));
            newPlatform = std::make_shared<world::stationaryPlatform>(x, y, nullptr);
            break;
        case world::platformType::horizontallyMoving:
            name = "horizontalPlatform";
            model = std::make_shared<repr::viewEntity>(name, name, 7.2,
                                                       std::make_shared<sf::Texture>(defaultTextures[name]));
            speed = 100 + rngFactory->getRNG()->generateRandomint(-50, 50);
            newPlatform = std::make_shared<world::horizontalPlatform>(x, y, speed, nullptr);
            break;
        case world::platformType::verticallyMoving:
            name = "verticalPlatform";
            model = std::make_shared<repr::viewEntity>(name, name, 7.2,
                                                       std::make_shared<sf::Texture>(defaultTextures[name]));
            speed = 100 + rngFactory->getRNG()->generateRandomint(-50, 50);
            newPlatform = std::make_shared<world::verticalPlatform>(x, y, speed, nullptr);
            break;
        case world::platformType::disappearing:
            name = "tempPlatform";
            model = std::make_shared<repr::viewEntity>(name, name, 7.2,
                                                       std::make_shared<sf::Texture>(defaultTextures[name]));
            model->initialiseAnimations(library);
            std::shared_ptr<repr::concreteAnimationObserver> obs =
                    std::make_shared<repr::concreteAnimationObserver>(model);
            newPlatform = std::make_shared<world::disappearingPlatform>(x, y, nullptr);
            newPlatform->setAnimationCamera(obs);
            break;
    }
    std::shared_ptr<repr::concreteCamera> cam = std::make_shared<repr::concreteCamera>(model);
    newPlatform->setpCam(cam);
    playerView->addEntity(model, 2);
    return newPlatform;
}

std::shared_ptr<world::bonusItem> repr::concreteFactory::produceBonus(int x, world::bonusType type) {
    std::shared_ptr<repr::viewEntity> model;
    std::shared_ptr<world::bonusItem> newBonus;
    std::string name;
    switch (type) {
        case world::bonusType::spring:
            name = "spring";
            model = std::make_shared<repr::viewEntity>(name, name, 0.38,
                                                       std::make_shared<sf::Texture>(defaultTextures[name]));
            newBonus = std::make_shared<world::bonusItem>(x, type);
            break;
        case world::bonusType::jetpack:
            name = "jetpack";
            model = std::make_shared<repr::viewEntity>(name, name, 0.115,
                                                       std::make_shared<sf::Texture>(defaultTextures[name]));
            newBonus = std::make_shared<world::bonusItem>(x, type);
            break;
        case world::bonusType::none:
            return nullptr; // shouldn't be reachable though
    }
    std::shared_ptr<repr::concreteCamera> cam = std::make_shared<repr::concreteCamera>(model);
    newBonus->setPCamera(cam);
    playerView->addEntity(model, 2);
    return newBonus;
}

std::shared_ptr<world::backgroundTile> repr::concreteFactory::produceBackgroundTile(int x, int y) {
    std::shared_ptr<repr::viewEntity> model;
    std::shared_ptr<world::backgroundTile> newTile;
    std::string name = "bgTile";
    model = std::make_shared<repr::viewEntity>(name, name, 0.0367,
                                               std::make_shared<sf::Texture>(defaultTextures[name]));
    newTile = std::make_shared<world::backgroundTile>(x, y);
    std::shared_ptr<repr::concreteCamera> cam = std::make_shared<repr::concreteCamera>(model);
    newTile->setpCam(cam);
    playerView->addEntity(model, 1);
    return newTile;
}


