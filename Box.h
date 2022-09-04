#ifndef BOX_H
#define BOX_H


#include "IShape.h"

class Box : public IShape
{
public:
    Box(const QPoint& begin, const QPoint& end);
    void draw(QPainter& painter) override;
private:
    QPoint begin, end;
    QColor penColor;
    QColor brushColor;
};

#endif // BOX_H
