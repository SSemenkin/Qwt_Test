#ifndef POINTGENERATOR_H
#define POINTGENERATOR_H

#include <QObject>
#include <QThread>

class PointGenerator : public QObject
{
    Q_OBJECT
public:
    explicit PointGenerator(QObject *parent = nullptr);
    ~PointGenerator();
    void start();
    void stop();

signals:
    void newPoint(float x, float y);

private:
    void generateNewRandomValues();

private:
    bool m_break {false};
};

#endif // POINTGENERATOR_H
