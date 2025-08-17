cmake_minimum_required(VERSION 3.28.3)
project(AP-project)

set(CMAKE_CXX_STANDARD 11)

# Find SFML package
find_package(SFML 2.6.1 COMPONENTS system window graphics network audio REQUIRED)
set(SRC_FILES
        main_source_files/main.cpp
        visual_source_files/view.cpp
        main_source_files/game.cpp
        visual_source_files/concreteFactory.cpp
        visual_source_files/viewEntity.cpp
        visual_source_files/concreteCamera.cpp
        visual_source_files/animationLibrary.cpp
)

add_executable(froggyjump ${SRC_FILES})


target_link_libraries(froggyjump ${CMAKE_SOURCE_DIR}/library/libFroggyJumpLibrary.so)

target_include_directories(froggyjump PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(froggyjump sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
