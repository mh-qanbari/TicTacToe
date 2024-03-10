find_package(Qt6 REQUIRED COMPONENTS Qml)

project(tictactoe_ui VERSION 1.0)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

qt_add_qml_module(${PROJECT_NAME}
    URI ui
    VERSION 1.0
    QML_FILES
        Board.qml
        DefaultPage.qml
        TileItem.qml
    RESOURCES
        icons/x.svg
        icons/o.svg
        icons/next.svg
        icons/prev.svg
    SOURCES
        boardmodel.h boardmodel.cpp
        tictactoe.h tictactoe.cpp
        Types.h
        SOURCES player.h player.cpp
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE Qt6::Qml
)
