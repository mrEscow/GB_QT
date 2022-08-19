#include "OpenFile.h"

OpenFile::OpenFile(QString name,QString path,QTextEdit* textEdit)
{
    this->name = name;
    this->path = path;
    this->textEdit.reset(textEdit);
}

void OpenFile::rename(const QString &name)
{
    this->name = name;
}

void OpenFile::changePath(const QString &path)
{
    this->path = path;
}

const QString &OpenFile::getName()
{
    return name;
}

const QString &OpenFile::getPath()
{
    return path;
}

QString OpenFile::getText()
{
    return textEdit.data()->toPlainText();
}
