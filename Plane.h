//
// Created by epsilon on 27.04.23.
//

#ifndef ZRK115_PLANE_H
#define ZRK115_PLANE_H

#include <utility>
#include <vector>
#include <queue>
#include "FlyingObject.h"

/**
   *  @brief Plane class
   */

class Plane : public FlyingObject{
public:
    Plane(int id_value, double x, double y, double v);
    ~Plane();

    void add_waypoint(std::pair<double, double> point);
    void update(double dt) override;

private:
    std::queue<std::pair<double, double>> waypoints;


};


#endif //ZRK115_PLANE_H