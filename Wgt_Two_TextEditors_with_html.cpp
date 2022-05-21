#include "Wgt_Two_TextEditors_with_html.h"
/*
    3. Создать программу, разместить два виджета QPlainTextEdit.
    Добавить две кнопки: первая кнопка будет добавлять текст из одного текстового виджета в другой,
    вторая кнопка - заменять текст в одном виджете на текст в другом виджете.
    Добавить третью кнопку, которая вставляет в один из текстовый виджет текст произвольного html-кода,
    например <font color='red'>Hello</font> (используйте метод setHtml(QString) ).
*/

#include <QLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QSpacerItem>
#include <QLabel>


Wgt_Two_TextEditors_with_html::Wgt_Two_TextEditors_with_html(QWidget * parent)
    : QWidget(parent)
{
    auto GroupBox = new QGroupBox(this);
    GroupBox->setTitle("Wgt_Two_TextEditors_with_html:");

    auto PlainText_WGT = new QWidget(this);
    PlainTextOne = new QPlainTextEdit(PlainText_WGT);
    PlainTextTwo = new QPlainTextEdit(PlainText_WGT);
    auto PlainLayout = new QHBoxLayout(PlainText_WGT);
    PlainLayout->addWidget(PlainTextOne);
    PlainLayout->addWidget(PlainTextTwo);

    auto Buttons_WGT = new QWidget(this);
    auto Add_Button = new QPushButton("AddText",Buttons_WGT);
    auto Replay_Button = new QPushButton(Buttons_WGT);
    auto HTML_Button = new QPushButton(Buttons_WGT);
    auto ButtonsLayout = new QHBoxLayout(Buttons_WGT);

    ButtonsLayout->addWidget(Add_Button);
    ButtonsLayout->addWidget(Replay_Button);
    ButtonsLayout->addWidget(HTML_Button);


    auto Main_V_Layout = new QVBoxLayout(this);
    Main_V_Layout->addWidget(PlainText_WGT);
    Main_V_Layout->addWidget(Buttons_WGT);

    GroupBox->setLayout(Main_V_Layout);

    this->move(10,10);
    this->resize(600,300);

    connect(Add_Button,SIGNAL(clicked()),this,SLOT(AddText()));
}

void  Wgt_Two_TextEditors_with_html::AddText(){
    qDebug()<< "AddText";
    PlainTextTwo->insertPlainText(PlainTextOne->toPlainText());
}
