#include "Star.h"

#include "qpainter.h"
#include "qpainterpath.h"
#include "qpen.h"
#include <cmath>

Star::Star(const QPoint& begin, const QPoint &end)
{
    this->begin = std::move(begin);
    this->end = std::move(end);
    penColor = QColor(qrand() % 255,qrand() % 255,qrand() % 255);
    brushColor = QColor(qrand() % 255,qrand() % 255,qrand() % 255);
    rotator = qrand() % 360;
}

void Star::draw(QPainter &painter)
{
    painter.setRenderHint(QPainter::Antialiasing);//
    painter.setRenderHint(QPainter::TextAntialiasing);//
    // Создаем 5 вершин пятиконечной звезды, предполагая, что начало координат находится в центре пятиконечной звезды
    begin - end;
    //qreal R = 100; // радиус // здесь для объяснения, qreal двойное значение под окнами и тип float во встроенном.
    qreal R = sqrt(pow((end.x()-begin.x()),2)+pow((end.y()-begin.y()),2)) / 2;
    const qreal Pi = 3.1415926;
    qreal deg = Pi * 72/180;

        QPoint points[5] = {
                            QPoint(R,0),
                            QPoint(R*cos(deg),-R*sin(deg)),
                            QPoint(R*cos(2*deg),-R*sin(2*deg)),
                            QPoint(R*cos(3*deg),-R*sin(3*deg)),
                            QPoint(R*cos(4*deg),-R*sin(4*deg)),
                            };


    // Установить шрифт
    QFont font;
    font.setPointSize(12);
    font.setBold(true);
    painter.setFont(font);


    // Устанавливаем кисть
    QPen penLine;
    penLine.setWidth (2); // Ширина линии
    penLine.setColor (penColor); // цвет линии
    //Qt::NoPen,Qt::SolidLine, Qt::DashLine, Qt::DotLine,Qt::DashDotLine,Qt::DashDotDotLine,Qt::CustomDashLine
    penLine.setStyle (Qt :: SolidLine); // Тип линии, сплошная линия, пунктирная линия и т. д.
    //Qt::FlatCap, Qt::SquareCap,Qt::RoundCap
    penLine.setCapStyle (Qt :: FlatCap); // Стиль окончания линии
    //Qt::MiterJoin,Qt::BevelJoin,Qt::RoundJoin,Qt::SvgMiterJoin
    penLine.setJoinStyle (Qt :: BevelJoin); // Стиль точки соединения линии
    painter.setPen(penLine);

    // Устанавливаем кисть
    QBrush  brush;
    brush.setColor (brushColor); // цвет кисти
    brush.setStyle (Qt :: SolidPattern); // стиль заливки кисти
    painter.setBrush(brush);  //

    // Дизайн и рисование PainterPath пятиконечной звезды для повторного использования
    QPainterPath starPath;
    starPath.moveTo(points[0]);
    starPath.lineTo(points[2]);
    starPath.lineTo(points[4]);
    starPath.lineTo(points[1]);
    starPath.lineTo(points[3]);
    starPath.closeSubpath (); // Закрываем путь, последняя точка соединяется с первой точкой

//    starPath.addText (points [0], font, "0"); // Отображаем номер конечной точки
//    starPath.addText(points[1],font,"1");
//    starPath.addText(points[2],font,"2");
//    starPath.addText(points[3],font,"3");
//    starPath.addText(points[4],font,"4");

    QPoint midlePoint = begin + ((end - begin) / 2);
    //Рисование
    painter.save (); // Сохраняем состояние координат
    painter.translate(midlePoint);
    painter.rotate(rotator);
    painter.drawPath (starPath); // Рисуем звезды
    painter.restore (); // Восстанавливаем состояние координат
}
