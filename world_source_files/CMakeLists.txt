cmake_minimum_required(VERSION 3.28.3)
project(FroggyJumpLibrary)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# Collect source files
set(SRC_FILES
        entity.cpp
        hitbox.cpp
        entitycamera.cpp
        stopwatch.cpp
        rng.cpp
        world.cpp
        singletons.cpp
        abstractFactory.cpp
        player.cpp
        platform.cpp
        bonusItem.cpp
        backgroundTile.cpp
        entity.h
        hitbox.h
        entitycamera.h
        stopwatch.h
        rng.h
        world.h
        singletons.h
        abstractFactory.h
        player.h
        platform.h
        bonusItem.h
        backgroundTile.h
)

# Build shared library
add_library(MyLibrary SHARED ${SRC_FILES})

# Optionally, specify the output name (without lib prefix)
set_target_properties(MyLibrary PROPERTIES OUTPUT_NAME "FroggyJumpLibrary")
