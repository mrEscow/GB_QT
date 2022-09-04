#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.begin(this);
        painter.drawPoint(50, 50); // x, y
        QPoint thPoint(50, 50);
        painter.drawPoint(thPoint); // по объекту точки
        QPointF thPointf(50., 50.);
        painter.drawPoint(thPointf);
    painter.end();
    this->render(this);

    painter.begin(this);
        painter.drawLine(0,0, 100, 100); // x1, y1, x2, y2
        QPoint p1 (0,0);
        QPoint p2 (100,100);
        painter.drawLine(p1,p2); // по двум точкам
        QLineF line(0,0,100,100);
        painter.drawLine(line); // по объекту “линия”
    painter.end();
    this->render(this);

    painter.begin(this);
    painter.drawRect(QRect(0,0,100,100));
    painter.drawRect(0, 20, 50, 50);
    painter.drawRect(QRectF(100, 120, 200, 200));
    painter.end();
    this->render(this);

    QPolygon polygon; // через объект QPolygon
    polygon << QPoint(0, height() - 10);
    polygon << QPoint(width() >> 1, 0);
    polygon << QPoint(width(), height() - 5);
    painter.drawPolygon(polygon);
    //Массив точек
    QPointF points[] = {
        QPointF(0,0),                           // 0
        QPointF(0,height() >> 1),               // 1
        QPointF(width() >> 1, height() >> 2),   // 2
        QPointF(width(),height()),              // 3
        QPointF(0,height()),                    // 4
    };
    painter.begin(this);
        painter.drawPolygon(points, sizeof(points) / sizeof(points[0]));
    painter.end();
    this->render(this);

    painter.begin(this);
        // Задаем координаты x и y верхнего угла, ширину и высоту
        painter.drawEllipse(50, 50, 50, 50);
        // Задаем прямоугольную область
        painter.drawEllipse(QRectF(50.0, 50.0, 50.0, 50.0));
        painter.drawEllipse(QRect(50, 50, 50, 50));
        // Задаем центр через класс точки и радиусы по осям x и y
        painter.drawEllipse(QPoint(50,50), 50, 50);
        painter.drawEllipse(QPointF(50.0,50.0), 50.0, 50.0);
    painter.end();
    this->render(this);


    QPainter painterHouse(this);
    int h = height() / 3;
    // Дом
    painterHouse.drawRect(5, h, width() - 10, height() - h - 10);
    int w = width() >> 1;
    // Крыша
    QPolygon polygonHouse;
    polygonHouse << QPoint(w, 5);
    polygonHouse << QPoint(5, h);
    polygonHouse << QPoint(width() - 5, h);
    painterHouse.drawPolygon(polygonHouse);
    // Окошко
    h = height() >> 1;
    painterHouse.drawRect(w - 50, h, 100, 100);
    painterHouse.drawLine(w, h, w, h + 100);
    painterHouse.end();
    this->render(this);

}

