//
// Created by epsilon on 04.05.23.
//

#include <iostream>
#include <valarray>
#include "Launcher.h"
#include "Missile.h"


Launcher::Launcher(double coordX, double coordY, double captureRange, int missilesCount) : coordX(coordX),
                                                                                           coordY(coordY),
                                                                                           capture_range(captureRange),
                                                                                           missiles_count(
                                                                                                   missilesCount)
                                                                                                   {active=true;
                                                                                                   targets_monitored = {};}

bool Launcher::is_active() {
    return active;
}

void Launcher::destroy() {
    std::cout << "Launcher at (" << coordX << ", " << coordY << ") was destroyed." << std::endl;
    active = false;
}

bool Launcher::check_collision(FlyingObject *object) {
    return (pow(object->get_coordinates().first - coordX, 2) + pow(object->get_coordinates().second - coordY, 2)
                <= pow(capture_range, 2) && object->is_active());
}

bool Launcher::monitor(FlyingObject *target, std::vector<FlyingObject *> &objects) {
    if (check_collision(target) && missiles_count >= 1) {
        std::cout << "collision" << std::endl;
        bool not_yet_fired = true;
        for (std::pair<FlyingObject&, int> fired: targets_monitored) {
            if (target->get_id() == fired.first.get_id()){
                not_yet_fired = false;
                if (fired.second < 2) {
                    fired.second += 1;
                    objects.push_back(new Missile(3, coordX, coordY, 5, 4, *target));
                    missiles_count -= 1;
                    return true;
                }
            }
        }
        if (not_yet_fired) {
            targets_monitored.emplace_back(*target, 1);
            objects.push_back(new Missile(4, coordX, coordY, 5, 4, *target));
            missiles_count -= 1;
            return true;
        }
    }
    return false;
}


Launcher::~Launcher() = default;

//TODO: Add to objects their class while destroyed
//TODO: fix hardcode in missles id
//TODO: fix targets checking