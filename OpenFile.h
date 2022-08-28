#ifndef OPENFILE_H
#define OPENFILE_H
#include <QString>
#include <QTextEdit>
#include <QSharedPointer>

class OpenFile
{
public:
    OpenFile(QString name,QString path,QTextEdit* textEdit);

    void rename(const QString& name);
    void changePath(const QString& path);

    const QString& getName();
    const QString& getPath();
    QString getText();
    QTextEdit* getTextEdit();

private:
    QString name;
    QString path;
    QTextEdit* textEdit;
};

#endif // OPENFILE_H
