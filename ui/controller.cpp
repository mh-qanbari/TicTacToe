#include "controller.h"
#include "TileState.h"

using namespace ui;

Controller *Controller::create()
{
    if (s_instance == nullptr)
        s_instance = new Controller;
    return s_instance;
}

Controller *Controller::create(QQmlEngine *, QJSEngine *)
{
    return Controller::create();
}

Controller::Controller(QObject *parent)
    : QObject{parent}
{
    registerTypes();
}

void Controller::registerTypes()
{
    ui::registerTileStateType();
}
