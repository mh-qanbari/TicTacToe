project(tictactoe_ui VERSION 1.0)

qt_add_qml_module(${PROJECT_NAME}
    URI ui
    VERSION 1.0
    QML_FILES
        Board.qml
        Tile.qml
    RESOURCES
        icons/x.svg
        icons/o.svg
)
