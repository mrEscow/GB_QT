#include "Box.h"
#include "qpainter.h"
#include "qpen.h"

Box::Box(const QPoint& begin, const QPoint &end)
{
    this->begin = std::move(begin);
    this->end = std::move(end);
    penColor = QColor(qrand() % 255,qrand() % 255,qrand() % 255);
    brushColor = QColor(qrand() % 255,qrand() % 255,qrand() % 255);
}

void Box::draw(QPainter &painter)
{
    QPen pan(penColor,5);
    painter.setPen(pan);

    QBrush brush(brushColor);
    painter.setBrush(brush);

    QRect rectangal(begin,end);
    painter.drawRect(rectangal);

    painter.end();
}
