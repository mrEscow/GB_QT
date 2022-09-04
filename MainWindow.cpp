#include "MainWindow.h"


#include "ui_MainWindow.h"

#include <QPainter>
#include <QPainterPath>

#include <math.h>

#include <QMouseEvent>

#include <QDebug>

#include "Box.h"
#include "Circle.h"
#include "Star.h"

//#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout,this, &MainWindow::slotTimerAlarm);
    //connect(timer, SIGNAL(timeout()), SLOT(slotTimerAlarm()));
    timer->start(100); // И запустим таймер
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    float retreat = 30.f;

    drawBox(QPoint(retreat,retreat),QPoint(width() - retreat, height() - retreat), Qt::red, Qt::yellow);

    drawCircl(QPoint(retreat,retreat),QPoint(width() - retreat, height() - retreat), Qt::black, Qt::darkMagenta);

    drawCircl(QPoint(width() * 1 / 5 + retreat, height() * 1 / 5 + retreat),QPoint(width() * 2 / 5 - retreat, height() * 3 / 5 - retreat), Qt::black, Qt::white);
    drawCircl(QPoint(width() * 3 / 5 + retreat, height() * 1 / 5 + retreat),QPoint(width() * 4 / 5 - retreat, height() * 3 / 5 - retreat), Qt::black, Qt::white);

    drawSmile(QPoint(retreat,retreat),QPoint(width() - retreat, height() - retreat), Qt::black, Qt::darkMagenta);


    drawStar(QPoint(width() / 2, height() / 2));


    for(auto snape: painters){
        QPainter painter(this);
        snape->draw(painter);
    }


}

void MainWindow::drawBox(const QPoint &begin, const QPoint &end, const QColor &colorFrame, const QColor &colorBrush)
{
    QPainter painter(this);

    QPen pan(colorFrame,5);
    painter.setPen(pan);

    painter.setBrush(QBrush(colorBrush));

    QRect rectangal(begin,end);
    painter.drawRect(rectangal);

    painter.end();
}

void MainWindow::drawCircl(const QPoint &begin, const QPoint &end, const QColor &colorFrame, const QColor &colorBrush)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    QPen pan(colorFrame,5);
    painter.setPen(pan);

    painter.setBrush(QBrush(colorBrush));

    QRect rectangal(begin,end);
    painter.drawEllipse(rectangal);

    painter.end();
}

void MainWindow::drawSmile(const QPoint &begin, const QPoint &end, const QColor &colorFrame, const QColor &colorBrush)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    QPen pan(colorFrame,5);
    painter.setPen(pan);

    QPainterPath painterPath;

    painterPath.moveTo((begin.x() + width() / 4) ,begin.y() + (3 * height()) / 4 );

    QPoint midle (width() / 2, height() / 2);
    painterPath.cubicTo(width() / 2, height() / 2 ,width() / 2 , height() , end.x() - width() / 4 , end.y() - height() / 4 );

    painter.drawPath(painterPath);

    painter.end();
}

void MainWindow::drawStar(const QPointF &center)
{
    QPainter painter (this); // Создаем объект QPainter
        painter.setRenderHint(QPainter::Antialiasing);//
        painter.setRenderHint(QPainter::TextAntialiasing);//
             // Создаем 5 вершин пятиконечной звезды, предполагая, что начало координат находится в центре пятиконечной звезды
             qreal R = 100; // радиус // здесь для объяснения, qreal двойное значение под окнами и тип float во встроенном.
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
             penLine.setColor (Qt :: blue); // цвет линии
        //Qt::NoPen,Qt::SolidLine, Qt::DashLine, Qt::DotLine,Qt::DashDotLine,Qt::DashDotDotLine,Qt::CustomDashLine
             penLine.setStyle (Qt :: SolidLine); // Тип линии, сплошная линия, пунктирная линия и т. д.
        //Qt::FlatCap, Qt::SquareCap,Qt::RoundCap
             penLine.setCapStyle (Qt :: FlatCap); // Стиль окончания линии
        //Qt::MiterJoin,Qt::BevelJoin,Qt::RoundJoin,Qt::SvgMiterJoin
             penLine.setJoinStyle (Qt :: BevelJoin); // Стиль точки соединения линии
        painter.setPen(penLine);

        // Устанавливаем кисть
        QBrush  brush;
             brush.setColor (Qt :: yellow); // цвет кисти
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

             starPath.addText (points [0], font, "0"); // Отображаем номер конечной точки
        starPath.addText(points[1],font,"1");
        starPath.addText(points[2],font,"2");
        starPath.addText(points[3],font,"3");
        starPath.addText(points[4],font,"4");


             //Рисование
             painter.save (); // Сохраняем состояние координат
        painter.translate(center);
             painter.drawPath (starPath); // Рисуем звезды
        painter.drawText(0,0,"S1");
             painter.restore (); // Восстанавливаем состояние координат

             painter.translate (center); // Перевод
             painter.scale (0.8,0.8); // Масштаб
             painter.rotate (90 + rotator); // Повернуть по часовой стрелке
             painter.drawPath (starPath); // Рисуем звезды
        painter.drawText(0,0,"S2");

             painter.resetTransform (); // Сбрасываем все преобразования координат
             painter.translate (center); // Перевод
             painter.rotate (-145 - rotator); // Повернуть против часовой стрелки
             painter.drawPath (starPath); // Рисуем звезды
             painter.drawText(0,0,"S3");
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() & Qt::LeftButton)
    {
        mousePosBegin = event->pos();
        qDebug () << "Левая кнопка мыши нажата:";
    }
    else if(event->button() & Qt::RightButton)
    {
        qDebug () << "Нажата правая кнопка мыши:";
    }
    else if(event->button() & Qt::MiddleButton)
    {
        qDebug () << "Нажата средняя кнопка мыши:";
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{

    if(event->button() & Qt::LeftButton)
    {
        mousePosEnd = event->pos();
        if(couter % 3 == 0){
            Box* box = new Box(mousePosBegin, mousePosEnd);
            painters.push_back(box);
        }
        if(couter % 3 == 1){
            Circle* circle = new Circle(mousePosBegin, mousePosEnd);
            painters.push_back(circle);
        }

        if(couter % 3 == 2){
            qDebug () << "ЗВЕЗДА!!!";
            Star* star = new Star(mousePosBegin, mousePosEnd);
            painters.push_back(star);
        }



        this->update();
        couter++;
        qDebug () << "Левая кнопка мыши отпущена:";
    }
    else if(event->button() & Qt::RightButton)
    {
        qDebug () << "Отпуск правой кнопкой мыши:";
    }
    else if(event->button() & Qt::MiddleButton)
    {
        qDebug () << "Отпуск средней кнопки мыши:";
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{

    if(event->buttons() & Qt::LeftButton)
    {
        qDebug () << "Переместить левую кнопку мыши вниз:";
    }
    if(event->buttons() & Qt::RightButton)
    {
        qDebug () << "Щелкните правой кнопкой мыши, чтобы переместить:";
    }
    if(event->buttons() & Qt::MiddleButton)
    {
        qDebug () << "Перемещение средней кнопки:";
    }
}

void MainWindow::slotTimerAlarm()
{
    //qDebug () << "MainWindow::slotTimerAlarm()";
    rotator++;
    this->update();
}

