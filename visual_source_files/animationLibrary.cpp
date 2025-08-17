//
// Created by waffle_laptop on 5/08/25.
//

#include "animationLibrary.h"
#include <iostream>

using namespace repr;

animationLibrary::animationLibrary(std::string folderPath) {
    readFolder(folderPath);
}

json animationLibrary::getAnimation(std::string entity, std::string anim) {
    return library[entity][anim];
}

void animationLibrary::readFolder(std::string folderPath) {
    std::string filePath = folderPath + "/animations.JSON";
    std::fstream filestream;
    filestream.open(filePath);
    if (not filestream.fail()) { // file exists
        json data = json::parse(filestream);
        std::string type = data["type"];
        for (auto i = data.begin(); i != data.end(); i++) {
            if (i.key() != "type") {
                library[type][i.key()] = i.value();
            }
        }
    } else {
        throw std::runtime_error("player animations data failed to load.\nPlease ensure"
                                 " assets/player/animations.JSON is present");
    }

}
