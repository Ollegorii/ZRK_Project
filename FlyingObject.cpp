//
// Created by epsilon on 27.04.23.
//

#include <cmath>
#include <iostream>
#include <tuple>
#include "FlyingObject.h"

FlyingObject::FlyingObject(int id_value, double fi, double theta, double z, double v):
id{id_value}, coordFi{fi}, coordTheta{theta}, coordZ{z}, velocity{v} {
    active = true;
}

FlyingObject::~FlyingObject() = default;

std::tuple<double, double, double> FlyingObject::get_coordinates() const{
    return std::tie(coordFi, coordTheta, coordZ);
}

double FlyingObject::get_velocity() {
    return velocity;
}

void FlyingObject::update(double minutes) {
    coordFi += vFi * minutes - 1. / 4;
    coordTheta += vTheta * minutes;
    coordZ += vZ * minutes;
}

void FlyingObject::set_target(double fi, double theta, double z) {
    //TODO: Count
    //double velocity = sqrt(pow(velX, 2) + pow(velY, 2));
    //double distance = sqrt(pow((x - coordX), 2) + pow((y - coordY), 2));
    //velX = velocity * ((x - coordX) / distance);
    //velY = velocity * ((y - coordY) / distance);
}

void FlyingObject::destroy() {
    std::cout << "Object at (" << coordX << ", " << coordY << ") was destroyed." << std::endl;
    active = false;
    //this->~FlyingObject();
}

bool FlyingObject::is_active() {
    return active;
}

bool FlyingObject::get_id() {
    return id;
}

