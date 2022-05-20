#ifndef WGT_CALCULATIONSIDETRIANGLE_ONTWOSIDES_AND_ANGLEBETWEEN_H
#define WGT_CALCULATIONSIDETRIANGLE_ONTWOSIDES_AND_ANGLEBETWEEN_H


#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QRadioButton>

class Wgt_CalculationSideTriangle_onTwoSides_and_AngleBetween : public QWidget
{
    Q_OBJECT
public:
    Wgt_CalculationSideTriangle_onTwoSides_and_AngleBetween(QWidget * parent = nullptr);
private slots:
    void Calculating_machine();
private:
    QLabel *Result_massege_Label;
    QLineEdit *LineEdit_A;
    QLineEdit *LineEdit_B;
    QLineEdit *LineEdit_C;
    QRadioButton *Radio_DEG;
    QRadioButton *Radio_RAD;
};

#endif // WGT_CALCULATIONSIDETRIANGLE_ONTWOSIDES_AND_ANGLEBETWEEN_H
