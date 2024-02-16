#ifndef MODELS_H
#define MODELS_H

#include <QApplication>
//#include "databasecontroller.h"

class Models
{
protected:


    int id;
    QString type;
    QString name;

public:
    Models (int id, QString type, QString name);
    Models ();

    virtual int getId ();
    virtual void setId (int id);

    virtual QString getType ();
    virtual void setType (QString type);

    virtual QString getName ();
//    virtual void setName (QString name);
};

class Aircrafts: public Models
{
private:
    int max_normal_G;
    int max_tan_G;
    int max_attack_angle;
    int area;
    int max_height;
    double max_M;

public:
    Aircrafts (QString name, int max_normal_G, int max_tan_G, int max_attack_angle,
               int area, int max_height, double max_M);
    Aircrafts ();

    int getMaxNormalG ();
//    void setMaxNormalG (int max_normal_G);

    int getMaxTanG ();
//    void setMaxTanG (int max_tan_G);

    int getMaxAttackAngle ();
//    void setMaxAttackAngle (int max_attack_angle);

    int getArea ();
//    void setArea (int area);

    int getMaxHeight();
//    void setMaxHeight (int max_height);

    double getMaxM ();
//    void setMaxM (double max_M);
};

class Missiles: public Models
{
private:
    int max_normal_G;
    int max_tan_G;
    int max_attack_angle;
    int area;
    int max_height;
    double max_M;

public:
    Missiles (QString name, int max_normal_G, int max_tan_G, int max_attack_angle,
               int area, int max_height, double max_M);
    Missiles ();

    int getMaxNormalG ();
//    void setMaxNormalG (int max_normal_G);

    int getMaxTanG ();
//    void setMaxTanG (int max_tan_G);

    int getMaxAttackAngle ();
//    void setMaxAttackAngle (int max_attack_angle);

    int getArea ();
//    void setArea (int area);

    int getMaxHeight();
//    void setMaxHeight (int max_height);

    double getMaxM ();
//    void setMaxM (double max_M);
};

class ABS: public Models
{
private:
    int max_attack_height;
    int max_attack_radius;
    int max_detection_height;
    int max_detection_radius;
    int max_attack_velocity;
    int attack_chance;
    int combat_kit;

public:
    ABS (QString name, int max_attack_height, int max_attack_radius,
         int max_detection_height, int max_detection_radius, int max_attack_velocity,
         int attack_chance, int combat_kit);
    ABS ();

    int getMaxAttackHeight ();
//    void setMaxAttackHeight (int max_attack_height);

    int getMaxAttackRadius ();
//    void setMaxAttackRadius (int max_attack_radius);

    int getMaxDetectionHeight ();
//    void setMaxDetectionHeight (int max_detection_height);

    int getMaxDetectionRadius ();
//    void setMaxDetectionRadius (int max_detection_radius);

    int getMaxAttackVelocity ();
//    void setMaxAttackVelocity (int max_attack_velocity);

    int getAttackChance ();
//    void setAttackChance (int attack_chance);

    int getCombatKit ();
//    void setCombatKit (int combat_kit);
};

#endif // MODELS_H
