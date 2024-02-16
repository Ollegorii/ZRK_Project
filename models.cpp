#include "models.h"

Models::Models (int id, QString type, QString name)
{
    this -> id = id;
    this -> type = type;
    this -> name = name;
}

Models::Models () {}
Aircrafts::Aircrafts () {}
Missiles::Missiles () {}
ABS::ABS () {}

int Models::getId () { return this -> id; }
void Models::setId (int id) { this -> id = id; }

QString Models::getType () { return this -> type; }
void Models::setType (QString type) { this -> type = type; }

QString Models::getName () { return this -> name; }
//void Models::setName (QString name) { this -> name = name; }

Aircrafts::Aircrafts (QString name, int max_normal_G, int max_tan_G, int max_attack_angle,
                      int area, int max_height, double max_M) : Models (0, "Aircraft", name)
{
    this -> max_normal_G = max_normal_G;
    this -> max_tan_G = max_tan_G;
    this -> max_attack_angle = max_attack_angle;
    this -> area = area;
    this -> max_height = max_height;
    this -> max_M = max_M;
}

int Aircrafts::getMaxNormalG () { return this -> max_normal_G; }
//void Aircrafts::setMaxNormalG (int max_normal_G) {this -> max_normal_G = max_normal_G; }

int Aircrafts::getMaxTanG () { return this -> max_tan_G; }
//void Aircrafts::setMaxTanG (int max_tan_G) {this -> max_tan_G = max_tan_G; }

int Aircrafts::getMaxAttackAngle () { return this -> max_attack_angle; }
//void Aircrafts::setMaxAttackAngle (int max_attack_angle) {this -> max_attack_angle = max_attack_angle; }

int Aircrafts::getArea () { return this -> area; }
//void Aircrafts::setArea (int area) {this -> area = area; }

int Aircrafts::getMaxHeight () { return this -> max_height; }
//void Aircrafts::setMaxHeight (int max_height) {this -> max_height = max_height; }

double Aircrafts::getMaxM () { return this -> max_M; }
//void Aircrafts::setMaxM (double max_M) {this -> max_M = max_M; }

Missiles::Missiles (QString name, int max_normal_G, int max_tan_G, int max_attack_angle,
                      int area, int max_height, double max_M) : Models (0, "Missile", name)
{
    this -> max_normal_G = max_normal_G;
    this -> max_tan_G = max_tan_G;
    this -> max_attack_angle = max_attack_angle;
    this -> area = area;
    this -> max_height = max_height;
    this -> max_M = max_M;
}

int  Missiles::getMaxNormalG () { return this -> max_normal_G; }
//void Missiles::setMaxNormalG (int max_normal_G) {this -> max_normal_G = max_normal_G; }

int Missiles::getMaxTanG () { return this -> max_tan_G; }
//void Missiles::setMaxTanG (int max_tan_G) {this -> max_tan_G = max_tan_G; }

int  Missiles::getMaxAttackAngle () { return this -> max_attack_angle; }
//void Missiles::setMaxAttackAngle (int max_attack_angle) {this -> max_attack_angle = max_attack_angle; }

int  Missiles::getArea () { return this -> area; }
//void Missiles::setArea (int area) {this -> area = area; }

int  Missiles::getMaxHeight () { return this -> max_height; }
//void Missiles::setMaxHeight (int max_height) {this -> max_height = max_height; }

double  Missiles::getMaxM () { return this -> max_M; }
//void Missiles::setMaxM (double max_M) {this -> max_M = max_M; }

ABS::ABS (QString name, int max_attack_height, int max_attack_radius,
          int max_detection_height, int max_detection_radius, int max_attack_velocity,
          int attack_chance, int combat_kit) : Models (0, "ABS", name)
{
    this -> max_attack_height = max_attack_height;
    this -> max_attack_radius = max_attack_radius;
    this -> max_detection_height = max_detection_height;
    this -> max_detection_radius = max_detection_radius;
    this -> max_attack_velocity = max_attack_velocity;
    this -> attack_chance = attack_chance;
    this -> combat_kit = combat_kit;
}

int ABS::getMaxAttackHeight () { return this -> max_attack_height; }
//void ABS::setMaxAttackHeight (int max_attack_height) { this -> max_attack_height = max_attack_height; }

int ABS::getMaxAttackRadius () { return this -> max_attack_radius; }
//void ABS::setMaxAttackRadius (int max_attach_radius) { this -> max_attack_radius = max_attack_radius; }

int ABS::getMaxDetectionHeight () { return this -> max_detection_height; }
//void ABS::setMaxDetectionHeight (int max_detection_height) { this -> max_detection_height = max_detection_height; }

int ABS::getMaxDetectionRadius () { return this -> max_detection_radius; }
//void ABS::setMaxDetectionRadius (int max_detection_radius) { this -> max_detection_radius = max_detection_radius; }

int ABS::getMaxAttackVelocity () { return this -> max_attack_velocity; }
//void ABS::setMaxAttackVelocity (int max_attack_velocity) { this -> max_attack_velocity = max_attack_velocity; }

int ABS::getAttackChance () { return this -> attack_chance; }
//void ABS::setAttackChance (int attack_chance) { this -> attack_chance = attack_chance; }

int ABS::getCombatKit () { return this -> combat_kit; }
//void ABS::setCombatKit (int combat_kit) { this -> combat_kit = combat_kit; }
