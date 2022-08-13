#ifndef SHORTCUTS_H
#define SHORTCUTS_H

#include "qnamespace.h"
#include "qpair.h"
struct Shortcuts{
    QPair<Qt::KeyboardModifier,Qt::Key> open;
    QPair<Qt::KeyboardModifier,Qt::Key> saveAs;
    QPair<Qt::KeyboardModifier,Qt::Key> createFile;
    QPair<Qt::KeyboardModifier,Qt::Key> exit;
};

#endif // SHORTCUTS_H
