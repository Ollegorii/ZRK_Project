//
// Created by epsilon on 27.04.23.
//

#include <valarray>
#include <iostream>
#include "Plane.h"

Plane::Plane(int id_value, double x, double y, DatabaseController* contr) : FlyingObject(id_value, x, y, 0, 0) {
    waypoints = {};
    this -> controller = contr;
    velX = controller->findAircraftById(id_value).cruising_speed * 0.0002;
    velY = controller->findAircraftById(id_value).cruising_speed * 0.0002;
    type = plane;
}

Plane::~Plane() = default;

void Plane::add_waypoint(std::pair<double, double> point) {
    waypoints.push(point);
    if (waypoints.size() == 1)
        set_target(waypoints.front().first, waypoints.front().second);
}

void Plane::update(double dt) {
    FlyingObject::update(dt);
    if (!waypoints.empty()){
        double velocity = sqrt(pow(velX, 2) + pow(velY, 2));
        if (std::abs(get_coordinates().first - waypoints.front().first) <=  velocity / 2 &&
             std::abs(get_coordinates().second - waypoints.front().second) <= velocity / 2) {
            std::cout << "Waypoint (" << waypoints.front().first << ", " << waypoints.front().second << ") achieved!"
                                                                                                    << std::endl;
            waypoints.pop();
            set_target(waypoints.front().first, waypoints.front().second);
        }
    }

    if (waypoints.empty())
        active = false;
}
