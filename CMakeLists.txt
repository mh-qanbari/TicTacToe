cmake_minimum_required(VERSION 3.20)

project(TicTacToeGame VERSION 1.0 LANGUAGES CXX)

SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Gui Quick QuickControls2)

add_executable(${PROJECT_NAME}
    main.cpp
    Algorithm.h Algorithm.cpp
    Board.h Board.cpp
    Controller.h Controller.cpp
    GameUtils.h GameUtils.cpp
    MinimaxAlgorithm.h MinimaxAlgorithm.cpp
    Tile.h Tile.cpp
    qml.qrc
)

target_include_directories(${PROJECT_NAME} PRIVATE src)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Gui
    Qt6::Quick
    Qt6::QuickControls2
)
