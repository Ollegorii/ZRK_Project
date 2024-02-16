//
// Created by epsilon on 27.04.23.
//

#include <cmath>
#include <iostream>
#include "FlyingObject.h"

FlyingObject::FlyingObject(int id_value, double x, double y, double v_x, double v_y):
id{id_value}, coordX{x}, coordY{y}, velX{v_x}, velY{v_y} {
    active = true;
}

FlyingObject::~FlyingObject() = default;

std::pair<double, double> FlyingObject::get_coordinates() const{
    return {coordX, coordY};
}

std::pair<double, double> FlyingObject::get_velocity() {
    return {velX, velY};
}

void FlyingObject::update(double dt) {
    coordX += velX * dt;
    coordY += velY * dt;
}

void FlyingObject::set_target(double x, double y) {
    double velocity = sqrt(pow(velX, 2) + pow(velY, 2));
    double distance = sqrt(pow((x - coordX), 2) + pow((y - coordY), 2));
    velX = velocity * ((x - coordX) / distance);
    velY = velocity * ((y - coordY) / distance);
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

int FlyingObject::get_type() {
    return type;
}
