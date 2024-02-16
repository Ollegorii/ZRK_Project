//
// Created by epsilon on 27.04.23.
//

#ifndef ZRK115_FLYINGOBJECT_H
#define ZRK115_FLYINGOBJECT_H


#include <utility>

/**
   *  @brief Parent class for flying things with some tools for kinematics
   */
enum Type
{
    plane,
    missile
};

class FlyingObject {
public:

    FlyingObject(int id_value, double x, double y, double v_x, double v_y);
    ~FlyingObject();

    std::pair<double, double> get_coordinates() const;
    std::pair<double, double> get_velocity();

    virtual void update(double dt);
    //void accelerate(double dt);
    void set_target(double x, double y);
    void destroy();
    bool is_active();
    bool get_id();
    int get_type();


protected:
    int id{};
    double coordX{}, coordY{}, velX{}, velY{};
    bool active;
    Type type;
};


#endif //ZRK115_FLYINGOBJECT_H
