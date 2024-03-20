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
enum class PlayerFlag {
    Undefined = 0,
    X,
    O,
};
Q_ENUM_NS(PlayerFlag)

static inline void registerTypes() {
    qmlRegisterUncreatableMetaObject(ui::staticMetaObject,
                                     "ui.types",
                                     1, 0,
                                     "Player",
                                     "Because PlayerFlag is enum");
    qmlRegisterType<PlayerFlag>("ui.types", 1, 0, "PlayerFlag");

    qmlRegisterUncreatableMetaObject(ui::staticMetaObject,
                                     "ui.types",
                                     1, 0,
                                     "Difficulty",
                                     "Because DifficultyLevel is enum");
    qmlRegisterType<DifficultyLevel>("ui.types", 1, 0, "DifficultyLevel");
}
}

#endif // UI_TYPES_H
