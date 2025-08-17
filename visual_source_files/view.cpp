#include "view.h"

using namespace repr;

view::view() : entities(11), height(-450),
               window(std::unique_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(700, 900),
                                                                             "doodle jump"))) {

    window->setVerticalSyncEnabled(true);

    if (!font.loadFromFile("assets/font.ttf")) { // loads the font
        throw std::runtime_error("font file failed to load.\nplease ensure this is texture is present in assets");
    }
}

void view::makeFrame(float time) {
    for (auto &layerVector: entities) {
        for (int entity = 0; entity < layerVector.size(); entity++) {
            if (layerVector[entity].expired()) { // clean up vector if pointer has expired
                layerVector.erase(layerVector.begin() + entity);
                entity--;
            } else {
                window->draw(layerVector[entity].lock()->getSprite(time, height)); // draws sprites
            }
        }
    }
    drawScore(floor(score + (height + 450) / 10));
    window->display(); // releases frame
    window->clear();   // clears window for next frame (internally, not on screen)
}

void view::addEntity(std::shared_ptr<viewEntity> _entity, int layer) {
    entities[layer].push_back(_entity);
}


void view::reset() {
    score = 0;
    height = -450;
    entities.clear();
    for (int index = 0; index <= 10; index++) {
        entities.push_back({});
    }
}

void view::updateHeight(float amount) {
    height = amount;
}

void view::updateScore(int amount) {
    score = amount;
}

void view::drawScore(int fullScore) {
    std::string Score = "score:";                               // string
    sf::Text text(Score, font);                                // text
    text.setFillColor(sf::Color::Black);                        // text colour set to black
    text.setPosition(350 - text.getLocalBounds().width / 2, 0); // text position is centered on the screen
    window->draw(text);                                         // draws the text
    Score = std::to_string(fullScore);
    text.setString(Score);
    text.setPosition(350 - text.getLocalBounds().width / 2, 30);
    window->draw(text);
}

void view::drawGameOverScreen() {
    std::fstream highscoreFile;
    highscoreFile.open("highscore.txt");
    std::string highscoreString;
    std::getline(highscoreFile, highscoreString); // reads the highscor file, should only be one line
    highscoreFile.close();
    if (highscoreString.size() == 0) { // if highscore file doesn't exist the string will be "" so it is set to "0"
        highscoreString = "0";
    }
    int highscore = stoi(highscoreString);
    std::string scoreOutputString = "Game Over";                 // string for text
    sf::Text text(scoreOutputString, font);                     // makes text
    text.setFillColor(sf::Color::White);                         // sets text colour to white
    text.setPosition(350 - text.getLocalBounds().width / 2, 20); // text is centered in the middle of the screen
    window->draw(text);                                          // draws the text
    if (highscore <
        floor(score + (height + 450) / 10)) { // if a new high score is achieved the old one won't be displayed
        std::ofstream highscoreUpdate("highscore.txt");
        highscoreUpdate << int(floor(score + (height + 450) / 10));
        highscoreUpdate.close();

        scoreOutputString = "new highscore:"; // draw highscore
        text.setString(scoreOutputString);
        text.setPosition(350 - text.getLocalBounds().width / 2, 60);
        window->draw(text);
        scoreOutputString = std::to_string(int(floor(score + (height + 450) / 10)));
        text.setString(scoreOutputString);
        text.setPosition(350 - text.getLocalBounds().width / 2, 100);
        window->draw(text);
        scoreOutputString = "press [R] to restart"; // draw message of how to restart
        text.setString(scoreOutputString);
        text.setPosition(350 - text.getLocalBounds().width / 2, 140);
        window->draw(text);
    } else { // if no new highscore is achieved the old one is also printed
        scoreOutputString = "highscore:"; // draws highscore
        text.setString(scoreOutputString);
        text.setPosition(350 - text.getLocalBounds().width / 2, 60);
        window->draw(text);
        scoreOutputString = std::to_string(highscore);
        text.setString(scoreOutputString);
        text.setPosition(350 - text.getLocalBounds().width / 2, 100);
        window->draw(text);
        scoreOutputString = "score:"; // draws score
        text.setString(scoreOutputString);
        text.setPosition(350 - text.getLocalBounds().width / 2, 140);
        window->draw(text);
        scoreOutputString = std::to_string(int(floor(score + (height + 450) / 10)));
        text.setString(scoreOutputString);
        text.setPosition(350 - text.getLocalBounds().width / 2, 180);
        window->draw(text);
        scoreOutputString = "press [R] to restart"; // draws message of how to restart
        text.setString(scoreOutputString);
        text.setPosition(350 - text.getLocalBounds().width / 2, 220);
        window->draw(text);
    }
    window->display();
}
