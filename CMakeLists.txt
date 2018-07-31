cmake_minimum_required(VERSION 2.8)
project(G52CPP)

# includes cmake/FindSDL2.cmake
set(CMAKE_MODULE_PATH ${G52CPP_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR})


set(SOURCE_FILES src/mainfunction.cpp 
src/BaseEngine.cpp
src/FontManager.cpp
src/TileManager.cpp
src/BouncingBallMain.cpp
src/BouncingBall.cpp
src/DisplayableObject.cpp
src/JPGImage.cpp
src/Demo1Main.cpp
src/Demo2Main.cpp
src/Demo2Object.cpp
src/Demo2TileManager.cpp
src/Demo3Main.cpp
src/Demo3Object.cpp
src/Demo3ObjectFinished.cpp
src/Demo3TileManager.cpp
src/Demo4Main.cpp
src/Demo4Object.cpp
src/Demo4TileManager.cpp
src/SimpleDemo.cpp
src/DisplayableObject.h
src/DemoAMain.h
src/header.h
src/Demo3Object.h
src/Demo2aMain.h
src/DemoBObject.h
src/Demo2Object.h
src/Demo3ObjectFinished.h
src/BaseEngine.h
src/SimpleDemo.h
src/TileManager.h
src/Demo3TileManager.h
src/Demo4TileManager.h
src/Demo3Main.h
src/FontManager.h
src/BouncingBall.h
src/Demo1Main.h
src/Demo2TileManager.h
src/Demo4Object.h
src/JPGImage.h
src/MyProjectMain.h
src/Demo4Main.h
src/MovementPosition.h
src/ViewerMain.h
src/BouncingBallMain.h
src/Demo2Main.h
src/templates.h
)

add_executable(SDL2_App ${SOURCE_FILES})
target_link_libraries(SDL2_App ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARY} ${SDL2_IMAGE_LIBRARY})

add_custom_command(TARGET SDL2_App PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${G52CPP_SOURCE_DIR}/src/resources ${CMAKE_CURRENT_BINARY_DIR})
