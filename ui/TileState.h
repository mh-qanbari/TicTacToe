#ifndef UI_TILESTATE_H
#define UI_TILESTATE_H

#include <QQmlEngine>

namespace ui {

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
}
}

#endif // UI_TILESTATE_H
