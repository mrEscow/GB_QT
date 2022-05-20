#include "Wgt_RootQuadraticEquationSecondDegree.h"

/*
    1. Написать программу,
    которая будет находить корень квадратного уравнения второй степени, входные данные: a, b, c.

    Если нахождение корня невозможно,
    выводить сообщение в поле результата (или выводить результат в виде комплексного числа).
    Учитывать, что число a может быть равно нулю.

    Данные для проверки:
    https://drive.google.com/file/d/1NZ4SnBaaFlIN2XzM5MiCfJV0uGZrae5X/view?usp=sharing
*/

#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QSpacerItem>
#include <QRegularExpressionValidator>

#include <QtMath>

Wgt_RootQuadraticEquationSecondDegree::Wgt_RootQuadraticEquationSecondDegree(QWidget * parent)
    : QWidget(parent)
{

    auto GroupBox = new QGroupBox(this);
    GroupBox->setTitle("The root of a quadratic equation of the second degree:");

    //-------------
    auto Name_WGT = new QWidget(this);
    auto MainLabel = new QLabel(Name_WGT);
    MainLabel->setText("ax^2+bx+c=0");
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
    auto ABC_WGT = new QWidget(this);

    QRegularExpression rx("-?\\d*");
    auto validator = new QRegularExpressionValidator(rx, ABC_WGT);

    auto wgt_a = new QWidget(ABC_WGT);
    auto A_Label = new QLabel(wgt_a);
    A_Label->setText("A");
    LineEdit_A = new QLineEdit(wgt_a);
    LineEdit_A->setValidator(validator);
    auto A_Layout = new QHBoxLayout(wgt_a);
    A_Layout->addWidget(A_Label,0);
    A_Layout->addWidget(LineEdit_A,1);


    auto wgt_b = new QWidget(ABC_WGT);
    auto B_Label = new QLabel(wgt_b);
    B_Label->setText("B");
    LineEdit_B = new QLineEdit(wgt_b);
    LineEdit_B->setValidator(validator);
    auto B_Layout = new QHBoxLayout(wgt_b);
    B_Layout->addWidget(B_Label);
    B_Layout->addWidget(LineEdit_B);

    auto wgt_c = new QWidget(ABC_WGT);
    auto C_Label = new QLabel(wgt_c);
    C_Label->setText("C");
    LineEdit_C = new QLineEdit(wgt_c);
    LineEdit_C->setValidator(validator);
    auto C_Layout = new QHBoxLayout(wgt_c);
    C_Layout->addWidget(C_Label);
    C_Layout->addWidget(LineEdit_C);

    auto ABC_Layout = new QHBoxLayout(ABC_WGT);
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

    auto Res_Label = new QLabel(ButtAndRes_WGT);
    Res_Label->setText("Result");
    Res_Label->setFont(font);

    auto ButtAndRes_Layout = new QHBoxLayout(ButtAndRes_WGT);
    ButtAndRes_Layout->addStretch();
    ButtAndRes_Layout->addWidget(Res_button);
    ButtAndRes_Layout->addStretch();
    ButtAndRes_Layout->addWidget(Res_Label);
    ButtAndRes_Layout->addStretch();
    //-------------

    auto V_Layout = new QVBoxLayout(this);
    V_Layout->addWidget(Name_WGT);
    V_Layout->addWidget(ABC_WGT);
    V_Layout->addWidget(ButtAndRes_WGT);

    GroupBox->setLayout(V_Layout);

    this->move(10,10);
    this->resize(600,300);

    connect(Res_button,SIGNAL(clicked()),this, SLOT(Calculating_machine()));
}

void Wgt_RootQuadraticEquationSecondDegree::Calculating_machine(){

    //Result_message;

    auto res = LineEdit_A->text().toInt() +
               LineEdit_B->text().toInt() +
               LineEdit_C->text().toInt();
    qDebug()<< "CONECT OK TEST RESULT: " << res;

}
