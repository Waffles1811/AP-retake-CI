#ifndef AP_ANIMATIONLIBRARY_H
#define AP_ANIMATIONLIBRARY_H

#include <map>
#include <string>
#include <fstream>
#include "../json.hpp"

using json = nlohmann::json;


namespace repr {
    class animationLibrary {
        std::unordered_map<std::string, std::unordered_map<std::string, json>> library; // outer map uses name of entity, inner map uses name of animation
    public:
        animationLibrary(std::string folderPath);// reads out all the animations in a folder
        ~animationLibrary() = default;

        /*
         *
         * looks for animations.JSON file in a folder, parses the JSON and stores it
         *
         */
        void readFolder(std::string folderPath);


        /*
         *
         * gives the data needed for the animation
         *
         * parameters:
         * entity: name of the entity type we want the animation of (e.g. player)
         * anim: name of the animation we want (e.g. jump)
         *
         * return: the data needed for the animation
         *
         */
        json getAnimation(std::string entity, std::string anim);
    };
}


#endif //AP_ANIMATIONLIBRARY_H
