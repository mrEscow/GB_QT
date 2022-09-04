#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "IShape.h"
#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    void drawBox(const QPoint& begin, const QPoint& end, const QColor& colorFrame = Qt::black, const QColor& colorBrush = Qt::white);
    void drawCircl(const QPoint& begin, const QPoint& end, const QColor& colorFrame = Qt::black, const QColor& colorBrush = Qt::white);
    void drawSmile(const QPoint& begin, const QPoint& end, const QColor& colorFrame = Qt::black, const QColor& colorBrush = Qt::white);
    void drawStar(const QPointF& center);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

public slots:
    void slotTimerAlarm();

private:
    Ui::MainWindow *ui;

    qreal rotator{0};

    QTimer *timer;

    QPoint mousePosBegin;
    QPoint mousePosEnd;
    QList<IShape*> painters;
    uint couter{0};
};
#endif // MAINWINDOW_H
