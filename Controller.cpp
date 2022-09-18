#include "Controller.h"

Controller::Controller(QObject *parent)
    : QObject{parent}
{

}

Controller::~Controller()
{
    if (findThread != nullptr) // При завершении нужно остановить поток,
    // если он существует
    {
        if (findThread->isRunning()) // Проверяем, работает ли поток
        {
            findThread->findStop(); // Меняем флаг для завершения всех циклов
            // потока
            findThread->terminate(); // Ожидаем завершения потока
        }
        findThread.reset(); // Сбрасываем поток, вызывая деструктор
    }
}

void Controller::startFind(QString dir, QString file)
{
    if (findThread.get())
    {
        findThread->findStop();
        findThread->terminate();
        findThread.reset();
        return;
    }

    findThread = QSharedPointer<ThreadFinder>::create(dir, file);

    findThread->start(QThread::NormalPriority);

    connect(findThread.get(), SIGNAL(stopedThread()), SLOT(deleteThread()));
    connect(findThread.get(), SIGNAL(writeFoundPath(QString)), SLOT(printCurrentPath(QString)));
    connect(findThread.get(), SIGNAL(findFile(QString)), SLOT(genStringPathFile(QString)));

    emit newFind();
}

void Controller::deleteThread()
{
    findThread.reset();
}

void Controller::printCurrentPath(QString path)
{
    currentPath = path;
    emit changFindPath(path);
}

void Controller::genStringPathFile(QString file)
{
    QString s = currentPath + file; // Формируем полный путь к файлу
    emit genPathOfFile(s); // Генерируем сигнал о готовности строки
    // файла
}

void Controller::finishThread()
{
    emit changFindPath(tr("FINISH. Find complete"));
}
