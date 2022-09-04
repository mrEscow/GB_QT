#ifndef CIRCLE_H
#define CIRCLE_H

#include "IShape.h"

class Circle : public IShape
{
public:
    Circle(const QPoint& begin, const QPoint& end);
    void draw(QPainter& painter) override;
private:
    QPoint begin, end;
    QColor penColor;
    QColor brushColor;
};

#endif // CIRCLE_H
