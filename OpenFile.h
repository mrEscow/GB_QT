#ifndef OPENFILE_H
#define OPENFILE_H
#include "MultilingualTextEdit.h"
#include <QString>
#include <QTextEdit>
#include <QSharedPointer>

class OpenFile
{
public:
    OpenFile(
            const QString& name,
            const QString& path,
            MultilingualTextEdit* textEdit);

    void rename(const QString& name);
    void changePath(const QString& path);

    const QString& getName();
    const QString& getPath();
    QString getText();
    MultilingualTextEdit* getTextEdit();

private:
    QString name;
    QString path;
    MultilingualTextEdit* textEdit;
};

#endif // OPENFILE_H
