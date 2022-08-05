#ifndef CHECKTEXT_H
#define CHECKTEXT_H

#include <QObject>
#include <QString>

class CheckText : public QObject
{
    Q_OBJECT
public:
    CheckText(QObject* parent = nullptr);
    void changeText(QString&);
};

#endif // CHECKTEXT_H
