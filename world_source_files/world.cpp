#include "world.h"

world::world::world(std::shared_ptr<abstractFactory> _factory, std::unique_ptr<scoreObserver> _scoreKeeper)
        : factory(std::move(_factory)), scoreKeeper(std::move(_scoreKeeper)), height(-450), lastPlatforms(-1500),
          difficulty(1) {}

bool world::world::time_up(float time) {
    for (int i = 0; i < platforms.size(); i++) {
        platforms[i]->timeUp(time);
        if (!platforms[i]->checkOnScreen(height)) {
            platforms.erase(platforms.begin() + i); // deletes the pointer and thus platform
        }
    }
    float oldPlayerY = playerchar->getYCoord();
    playerchar->timeUp(time);
    if (playerchar->getYCoord() > height) {
        height = playerchar->getYCoord();
        scoreKeeper->updateHeight(height); // update score
        for (auto i: bgTiles) {
            i->newHeight(height); // update background
        }
        if (height - lastPlatforms > 130 + difficulty * 15) {
            factory->producePlatforms(height + 550, difficulty, platforms);
            lastPlatforms = height; // potentially spawn new platforms
        }
        difficulty = std::min(5, int(std::floor((height / 4000) + 1))); // update difficulty
    }
    for (auto &i: platforms) {
        if (playerchar->getHitbox()->detectCollision(*i->getHitbox(), playerchar->getYCoord() - oldPlayerY)) {
            if (i->getIsJumpedOn()) {
                scoreKeeper->updateScore(-20); // deduct score if already jumped on
            }
            playerchar->handleCollision(i);
        }
    }
    if (playerchar->getYCoord() < height - 450) {
        return true;
    }
    return false;
}

void world::world::processInputs(movement id) {
    playerchar->processInput(id);
}

void world::world::setup() {
    std::thread background(&world::setupBackground, this); // take a while so separate thread to make it a bit faster
    playerchar = factory->producePlayer(350, -600, 10, 3.38);
    platforms.push_back(factory->producePlatform(350, -700, platformType::stationary)); // spawn platform under player
    factory->producePlatforms(-600, 1, platforms);
    factory->producePlatforms(-400, 1, platforms);
    factory->producePlatforms(-200, 1, platforms);
    factory->producePlatforms(0, 1, platforms);
    background.join();
}

void world::world::setupBackground() {
    for (int i = 0; i < 37; i++) {
        for (int j = 0; j < 28; j++) {
            bgTiles.push_back(
                    factory->produceBackgroundTile((700 / 28 * j), -(900 / 36 * i))); // spawns all background tiles
        }
    }
}

void world::world::reset() {
    height = -450;
    scoreKeeper->reset();
    playerchar = nullptr;
    platforms.clear();
    difficulty = 1;
    lastPlatforms = -1500;
}
