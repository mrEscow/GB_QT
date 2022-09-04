#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void paintEvent(QPaintEvent *event);
private:
    void drawBox(const QPoint& begin, const QPoint& end, const QColor& colorFrame = Qt::black, const QColor& colorBrush = Qt::white);
    void drawCircl(const QPoint& begin, const QPoint& end, const QColor& colorFrame = Qt::black, const QColor& colorBrush = Qt::white);
    void drawSmile(const QPoint& begin, const QPoint& end, const QColor& colorFrame = Qt::black, const QColor& colorBrush = Qt::white);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
