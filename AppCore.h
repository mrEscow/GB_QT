#ifndef APPCORE_H
#define APPCORE_H

#include <QObject>
#include "ConteinerForQML.h"

class AppCore : public QObject
{
    Q_OBJECT
public:
    AppCore(QObject *parent = nullptr);
    ~AppCore();

    Q_INVOKABLE void setDate(const QString& task,const QString& date,const QString& priprity);
    Q_INVOKABLE QStringList getDates();
    Q_INVOKABLE void removeDate(const int& index);

private:
    void save();
    void load();
    QString fileName;
    QList<ConteinerForQML> dateConteiners;
};

#endif // APPCORE_H
