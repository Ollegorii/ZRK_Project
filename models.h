#ifndef MODELS_H
#define MODELS_H

#include <QApplication>
#include "databasecontroller.h"

class Model
{
public:
    Model ();
    Model (int id, QString name);

    int id;
    QString name;
};

class Aircraft : public Model
{
public:
    Aircraft ();
    Aircraft (int id, QString name, int area, int max_height, double max_M, int cruising_speed);

    int area;
    int max_height;
    double max_M;
    int cruising_speed;
};

class Missile : public Model
{
public:
    Missile ();
    Missile (int id, QString name, int area, int max_height, double max_M, int cruising_speed);

    int area;
    int max_height;
    double max_M;
    int cruising_speed;
};

class ABS : public Model
{
public:
    ABS ();
    ABS (int id, QString name, int max_attack_height, int max_attack_radius,
        int max_detection_height, int max_detection_radius, int max_attack_velocity,
        int attack_chance, int combat_kit);

    int max_attack_height;
    int max_attack_radius;
    int max_detection_height;
    int max_detection_radius;
    int max_attack_velocity;
    int attack_chance;
    int combat_kit;
};

#endif // MODELS_H
