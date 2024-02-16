//
// Created by epsilon on 28.04.23.
//

#include "Missile.h"

/**
   *  @brief Class for presenting Missiles
   */

Missile::Missile(int id_value, double x, double y, double vX, double vY, FlyingObject &target) : FlyingObject(id_value, x, y, vX, vY),
                                                                                         target(target) {
    std::cout << "Missile at (" << x << ", " << y << ") was created" << std::endl;
    type = missile;
}

Missile::~Missile() = default;

void Missile::update(double dt) {
    FlyingObject::update(dt);
    set_target(target.get_coordinates().first, target.get_coordinates().second);
    //TODO: Check if target is destroyed
    double velocity = sqrt(pow(velX, 2) + pow(velY, 2));
    if (target.is_active()) {
        if (std::abs(coordX - target.get_coordinates().first) <= velocity / 2 &&
            std::abs(coordY - target.get_coordinates().second) <= velocity / 2) {
            target.destroy();
            this->destroy();
        }
    } else {
        this->destroy();
    }
}
