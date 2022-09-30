#ifndef APPCORE_H
#define APPCORE_H

#include <QObject>

class AppCore : public QObject
{
    Q_OBJECT
public:
    AppCore(QObject *parent = nullptr);
    ~AppCore();
};

#endif // APPCORE_H
