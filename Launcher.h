//
// Created by epsilon on 04.05.23.
//

#ifndef ZRK115_LAUNCHER_H
#define ZRK115_LAUNCHER_H


#include <vector>
#include "FlyingObject.h"

class Launcher {
public:
    Launcher(double coordX, double coordY, double captureRange, int missilesCount);
    ~Launcher();

    void destroy();
    bool is_active();
    bool monitor(FlyingObject *target, std::vector<FlyingObject*> &objects);

private:
    double coordX{}, coordY{};
    double capture_range{};
    int missiles_count{};
    bool active;
    bool check_collision(FlyingObject *object);
    std::vector<std::pair<FlyingObject&, int>> targets_monitored;


};

#endif //ZRK115_LAUNCHER_H
//TODO: ADD MISSILES AND ZRK TYPES FROM DB. THE SAME FOR PLANES.