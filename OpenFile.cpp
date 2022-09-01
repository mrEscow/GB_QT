#include "OpenFile.h"

OpenFile::OpenFile(const QString &name, const QString &path, MultilingualTextEdit *textEdit)
{
    this->name = std::move(name);
    this->path = std::move(path);
    this->textEdit = textEdit;
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
    return textEdit->toPlainText();
}

MultilingualTextEdit *OpenFile::getTextEdit()
{
    return textEdit;
}
