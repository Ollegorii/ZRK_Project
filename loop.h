#ifndef LOOP_H
#define LOOP_H
#include <vector>
#include <QTest>
#include "FlyingObject.h"
#include "Launcher.h"
#include <cmath>
#include "FlyingObject.h"

class Loop : public QObject
{
    Q_OBJECT
public:
    Loop();
    Loop(std::vector<FlyingObject*> fobj, std::vector<Launcher*> lch) {flyobjects = fobj; launchers = lch;};
    void start();

private:
    std::vector<FlyingObject*> flyobjects;
    std::vector<Launcher*> launchers;

signals:
    void drawPoint(std::pair<double, double> point, double angle);
    void drawMissilePoint(std::pair<double, double> point, double angle);
    void drawLine(std::vector<std::pair<double, double>> points);
    void drawRadar(const std::vector<Launcher*> launchers, double radius);

};

#endif // LOOP_H
