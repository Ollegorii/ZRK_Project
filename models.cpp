#include "models.h"

Model::Model () {}
Aircraft::Aircraft () {}
Missile::Missile () {}
ABS::ABS () {}

Model::Model (int id, QString name)
{
    this -> id = id;
    this -> name = name;
}

Aircraft::Aircraft (int id, QString name, int area, int max_height, double max_M, int cruising_speed) : Model (id, name)
{
    this -> area = area;
    this -> max_height = max_height;
    this -> max_M = max_M;
    this -> cruising_speed = cruising_speed;
}

Missile::Missile (int id, QString name, int area, int max_height, double max_M, int cruising_speed) : Model (id, name)
{
    this -> area = area;
    this -> max_height = max_height;
    this -> max_M = max_M;
    this -> cruising_speed = cruising_speed;
}

ABS::ABS (int id, QString name, int max_attack_height, int max_attack_radius,
          int max_detection_height, int max_detection_radius, int max_attack_velocity,
          int attack_chance, int combat_kit) : Model (id, name)
{
    this -> max_attack_height = max_attack_height;
    this -> max_attack_radius = max_attack_radius;
    this -> max_detection_height = max_detection_height;
    this -> max_detection_radius = max_detection_radius;
    this -> max_attack_velocity = max_attack_velocity;
    this -> attack_chance = attack_chance;
    this -> combat_kit = combat_kit;
}
