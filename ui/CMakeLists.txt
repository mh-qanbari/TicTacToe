find_package(Qt6 REQUIRED COMPONENTS Qml)

project(tictactoe_ui VERSION 1.0)

qt_add_qml_module(${PROJECT_NAME}
    URI ui
    VERSION 1.0
    QML_FILES
        Board.qml
        TileItem.qml
    RESOURCES
        icons/x.svg
        icons/o.svg
    SOURCES
        controller.h controller.cpp
        TileState.h
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE Qt6::Qml
)
