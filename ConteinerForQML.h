#ifndef CONTEINERFORQML_H
#define CONTEINERFORQML_H
#include <QString>
#include <QList>

class ConteinerForQML
{
public:
    ConteinerForQML(const QString &task, const QString &time, const QString &prog);
    QString getTask() const;
    QString getTime() const;
    QString getPprog() const;
private:
    QString task;
    QString time;
    QString prog;
};

#endif // CONTEINERFORQML_H
