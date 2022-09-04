#ifndef ISHAPE_H
#define ISHAPE_H

#endif // ISHAPE_H

#pragma once
#include <QWidget>

class IShape
{
public:
    virtual void draw(QPainter& painter) = 0;
};
