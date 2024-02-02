cmake_minimum_required(VERSION 3.15)
project(SimpleSnake)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

set(CMAKE_CXX_STANDARD 20)

SET(CMAKE_CXX_FLAGS "-lsfml-graphics -lsfml-window -lsfml-system")

add_executable(SimpleSnake main.cpp managers/GameManager.cpp managers/GameManager.h gameElements/snake/SnakeModel.cpp gameElements/snake/SnakeModel.h fields/base/BaseEnumField.h fields/base/BaseField.h fields/SnakeSectionStatusField.cpp fields/SnakeSectionStatusField.h gameElements/snake/SnakePiece.cpp gameElements/snake/SnakePiece.h Resources.h managers/HudManager.cpp managers/HudManager.h managers/FieldManager.cpp managers/FieldManager.h gameElements/Apple.cpp gameElements/Apple.h)
