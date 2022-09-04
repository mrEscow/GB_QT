#ifndef STAR_H
#define STAR_H

#include "IShape.h"

class Star : public IShape
{
public:
    Star(const QPoint& begin, const QPoint& end);
    void draw(QPainter& painter) override;
private:
    QPoint begin, end;
    QColor penColor;
    QColor brushColor;
    qreal rotator;
};

#endif // STAR_H
