#include "pointgenerator.h"

PointGenerator::PointGenerator(QObject *parent) : QObject(parent)
{
    moveToThread(new QThread(this));

    QObject::connect(thread(), &QThread::started, this, &PointGenerator::generateNewRandomValues);
}

PointGenerator::~PointGenerator()
{
    m_break = true;
    while (thread()->isRunning());
}

void PointGenerator::start()
{
    if (!thread()->isRunning()) {
        m_break = false;
        thread()->start();
    }
}

void PointGenerator::stop()
{
    m_break = true;
}

void PointGenerator::generateNewRandomValues()
{
    srand(time(0));
    for(;;) {
        emit newPoint(rand() % 100, rand() % 100);
        thread()->msleep(1300);
        if (m_break) {
            thread()->quit();
            break;
        }
    }
}
