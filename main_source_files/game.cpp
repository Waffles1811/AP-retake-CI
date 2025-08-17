#include "game.h"

game::game() {
    playerView = std::make_shared<repr::view>();
    stopwatchInc = std::unique_ptr<world::stopwatchFactory>(new world::stopwatchFactory());
    std::shared_ptr<repr::concreteFactory> factory = std::make_shared<repr::concreteFactory>(playerView);
    std::unique_ptr<world::scoreObserver> obs =
            std::unique_ptr<repr::concreteScoreObserver>(new repr::concreteScoreObserver(playerView));
    world = std::unique_ptr<world::world>(new world::world(factory, std::move(obs)));
}

void game::setup() {
    world->setup();
}


void game::mainGameLoop() {
    float timeSinceLastTic = 0;
    stopwatchInc->getStopwatch()->gameTimeTic();
    // called here so it isn't too long later
    while (playerView->window->isOpen()) {
        timeSinceLastTic = stopwatchInc->getStopwatch()->gameTimeTic();
        processInputs();
        if (world->time_up(timeSinceLastTic)) { // world->time_up(..) returns true if the player fell off the screen
            gameOver();
            playerView->reset(); // reset everything to restart the garme
            world->reset();
            setup();
            timeSinceLastTic = stopwatchInc->getStopwatch()->gameTimeTic();
        }
        playerView->makeFrame(timeSinceLastTic);
    }
}


void game::processInputs() {
    sf::Event event;
    while (playerView->window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Left or event.key.code == sf::Keyboard::A) {
                    // ^ maybe change this back to scancode on windows, didn't work on linux for me
                    world->processInputs(movement::moveLeft);
                } else if (event.key.code == sf::Keyboard::Right or event.key.code == sf::Keyboard::D) {
                    world->processInputs(movement::moveRight);
                } else if (event.key.code == sf::Keyboard::Escape) {
                    playerView->window->close();
                }
                break;
            case sf::Event::KeyReleased:
                if (event.key.code == sf::Keyboard::Left or event.key.code == sf::Keyboard::A) {
                    world->processInputs(movement::stopLeft);
                } else if (event.key.code == sf::Keyboard::Right or event.key.code == sf::Keyboard::D) {
                    world->processInputs(movement::stopRight);
                }
                break;
            case sf::Event::Closed:
                playerView->window->close(); // also exits program
                return;
        }
    }
}

void game::gameOver() {
    playerView
            ->drawGameOverScreen(); // draws the game over screen which stays on screen for the duration of this function
    while (playerView->window->isOpen()) {
        sf::Event event;
        while (playerView->window->pollEvent(event)) {
            switch (event.type) {
                case sf::Event::KeyPressed:
                    if (event.key.code ==
                        sf::Keyboard::R) { // maybe change this back to scancode on windows, didn't work on linux for me
                        return;
                    }
                    break;

                case sf::Event::Closed:
                    playerView->window->close(); // also exits program
                    return;
            }
        }
    }
}


