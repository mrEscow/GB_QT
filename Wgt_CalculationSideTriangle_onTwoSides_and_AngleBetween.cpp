#include "Wgt_CalculationSideTriangle_onTwoSides_and_AngleBetween.h"
/*
    2. Расчет стороны треугольника по двум сторонам и углом между ними.

    Дополнительно:
        добавить переключатель из QRadioButton для выбора единиц, в каких указан угол: градусах или радианах.

    Формулу для расчета можно найти по ссылке: https://www-formula.ru/2011-10-09-11-08-41.

    Данные для проверки:
        a=3, b=4, угол=900 => результат = 5
*/


#include <QLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QSpacerItem>
#include <QRegularExpressionValidator>

#include <QtMath>

Wgt_CalculationSideTriangle_onTwoSides_and_AngleBetween::Wgt_CalculationSideTriangle_onTwoSides_and_AngleBetween(QWidget * parent)
    : QWidget(parent)
{
    auto GroupBox = new QGroupBox(this);
    GroupBox->setTitle("Calculation of the side of a triangle on two sides and the angle between them:");
    //GroupBox->resize(550,250);
    //-------------
    auto Name_WGT = new QWidget(this);
    auto MainLabel = new QLabel(Name_WGT);
    MainLabel->setText("a = [квадратный корень]( b^2 + c^2 - 2*b*c*cos(α) )");
    auto font = MainLabel->font();
    font.setBold(true);
    font.setPixelSize(20);
    MainLabel->setFont(font);

    auto Name_Layout = new QHBoxLayout(Name_WGT);
    Name_Layout->addStretch();
    Name_Layout->addWidget(MainLabel);
    Name_Layout->addStretch();
    //-------------
    //-------------
    auto INPUT_WGT = new QWidget(this);

    QRegularExpression rx("-?\\d*");
    auto validator = new QRegularExpressionValidator(rx, INPUT_WGT);

    auto wgt_a = new QWidget(INPUT_WGT);
    auto A_Label = new QLabel(wgt_a);
    A_Label->setText("B");
    LineEdit_A = new QLineEdit(wgt_a);
    LineEdit_A->setValidator(validator);
    auto A_Layout = new QHBoxLayout(wgt_a);
    A_Layout->addWidget(A_Label,0);
    A_Layout->addWidget(LineEdit_A,1);


    auto wgt_b = new QWidget(INPUT_WGT);
    auto B_Label = new QLabel(wgt_b);
    B_Label->setText("C");
    LineEdit_B = new QLineEdit(wgt_b);
    LineEdit_B->setValidator(validator);
    auto B_Layout = new QHBoxLayout(wgt_b);
    B_Layout->addWidget(B_Label);
    B_Layout->addWidget(LineEdit_B);

    auto wgt_c = new QWidget(INPUT_WGT);
    auto C_Label = new QLabel(wgt_c);
    C_Label->setText("Angel");
    LineEdit_C = new QLineEdit(wgt_c);
    LineEdit_C->setValidator(validator);
    auto C_Layout = new QHBoxLayout(wgt_c);
    C_Layout->addWidget(C_Label);
    C_Layout->addWidget(LineEdit_C);

    auto ABC_Layout = new QHBoxLayout(INPUT_WGT);
    ABC_Layout->addWidget(wgt_a);
    ABC_Layout->addWidget(wgt_b);
    ABC_Layout->addWidget(wgt_c);
    //-----------------

    //-------------
    auto ButtAndRes_WGT = new QWidget(this);
    font.setPixelSize(16);

    auto Res_button = new QPushButton(ButtAndRes_WGT);
    Res_button->setText("Result");
    Res_button->setFont(font);

    Result_massege_Label = new QLabel(ButtAndRes_WGT);
    Result_massege_Label->setText("Result");
    Result_massege_Label->setFont(font);

    auto ButtAndRes_Layout = new QHBoxLayout(ButtAndRes_WGT);
    ButtAndRes_Layout->addStretch();
    ButtAndRes_Layout->addWidget(Res_button);
    ButtAndRes_Layout->addStretch();
    ButtAndRes_Layout->addWidget(Result_massege_Label);
    ButtAndRes_Layout->addStretch();
    //-------------

    auto V_Layout = new QVBoxLayout(this);
    V_Layout->addWidget(Name_WGT);
    V_Layout->addWidget(INPUT_WGT);
    V_Layout->addWidget(ButtAndRes_WGT);


    GroupBox->setLayout(V_Layout);

    this->move(10,10);
    this->resize(600,300);

    connect(Res_button,SIGNAL(clicked()),this, SLOT(Calculating_machine()));
}

void Wgt_CalculationSideTriangle_onTwoSides_and_AngleBetween::Calculating_machine(){
    QString Result_message;
    auto b = LineEdit_A->text().toInt();
    auto c = LineEdit_B->text().toInt();
    auto angel = LineEdit_C->text().toInt();

    auto res = qSqrt((b*b) + (c*c) - ((2*b*c)*qCos(angel)));

    qDebug() << "Result:" << res;
}
