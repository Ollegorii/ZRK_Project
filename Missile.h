//
// Created by epsilon on 28.04.23.
//

#ifndef ZRK115_MISSILE_H
#define ZRK115_MISSILE_H

#include <valarray>
#include <iostream>
#include "FlyingObject.h"
#include "Plane.h"

class Missile : public FlyingObject{

public:
    Missile(int id_value, double x, double y, double vX, double vY, FlyingObject &target);
    ~Missile();

    void update(double dt) override;

private:
    FlyingObject &target;
};


#endif //ZRK115_MISSILE_H

