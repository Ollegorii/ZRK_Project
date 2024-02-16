//
// Created by epsilon on 27.04.23.
//

#ifndef ZRK115_FLYINGOBJECT_H
#define ZRK115_FLYINGOBJECT_H


#include <utility>

/**
   *  @brief Parent class for flying things with some tools for kinematics
   */

class FlyingObject {
public:

    FlyingObject(int id_value, double fi, double theta, double z, double v);
    ~FlyingObject();

    std::tuple<double, double, double> get_coordinates() const;
    double get_velocity();

    virtual void update(double minutes);
    //void accelerate(double dt);
    void set_target(double fi, double theta, double z);
    void destroy();
    bool is_active();
    bool get_id();



protected:
    int id{};
    double coordFi{}, coordTheta{}, coordZ{}, velocity{};
    double vFi, vTheta, vZ;
    bool active;
};


#endif //ZRK115_FLYINGOBJECT_H
