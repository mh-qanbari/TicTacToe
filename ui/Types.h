#ifndef UI_TYPES_H
#define UI_TYPES_H

#include <QQmlEngine>

namespace ui {
Q_NAMESPACE
enum class DifficultyLevel {
    Easy,
    Medium,
    Hard
};
Q_ENUM_NS(DifficultyLevel)

Q_NAMESPACE
enum class TileState {
    Undefined = 0,
    X,
    O,
};
Q_ENUM_NS(TileState)

static inline void registerTileStateType() {
    qmlRegisterUncreatableMetaObject(ui::staticMetaObject,
                                     "ui.types",
                                     1, 0,
                                     "Tile",
                                     "Because TileState is enum");
    qmlRegisterType<TileState>("ui.types", 1, 0, "TileState");

    qmlRegisterUncreatableMetaObject(ui::staticMetaObject,
                                     "ui.types",
                                     1, 0,
                                     "Difficulty",
                                     "Because DifficultyLevel is enum");
    qmlRegisterType<DifficultyLevel>("ui.types", 1, 0, "DifficultyLevel");
}
}

#endif // UI_TYPES_H
