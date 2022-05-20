#ifndef WGT_ROOTQUADRATICEQUATIONSECONDDEGREE_H
#define WGT_ROOTQUADRATICEQUATIONSECONDDEGREE_H

#include <QWidget>
#include <QLineEdit>

class Wgt_RootQuadraticEquationSecondDegree : public QWidget
{
    Q_OBJECT
public:
    Wgt_RootQuadraticEquationSecondDegree(QWidget * parent = nullptr);
private slots:
    void Calculating_machine();
private:
    QString Result_message;

    QLineEdit *LineEdit_A;
    QLineEdit *LineEdit_B;
    QLineEdit *LineEdit_C;
};

#endif // WGT_ROOTQUADRATICEQUATIONSECONDDEGREE_H
