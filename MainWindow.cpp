#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QPainter>
#include <QPainterPath>

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
    float retreat = 30.f;

    drawBox(QPoint(retreat,retreat),QPoint(width() - retreat, height() - retreat), Qt::red, Qt::yellow);

    drawCircl(QPoint(retreat,retreat),QPoint(width() - retreat, height() - retreat), Qt::black, Qt::darkMagenta);

    drawCircl(QPoint(width() * 1 / 5 + retreat, height() * 1 / 5 + retreat),QPoint(width() * 2 / 5 - retreat, height() * 3 / 5 - retreat), Qt::black, Qt::white);
    drawCircl(QPoint(width() * 3 / 5 + retreat, height() * 1 / 5 + retreat),QPoint(width() * 4 / 5 - retreat, height() * 3 / 5 - retreat), Qt::black, Qt::white);

    drawSmile(QPoint(retreat,retreat),QPoint(width() - retreat, height() - retreat), Qt::black, Qt::darkMagenta);
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

