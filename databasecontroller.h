#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

#include <QtSql>
#include "models.h"

class DatabaseController
{
private:
    int modelsCounter;

    void setModelsCounter ();
    bool addModel (Models* model);

public:
    QSqlDatabase db;

    DatabaseController (QString filename);

    void addAircraft (Aircrafts* aircraft);
    void addMissile (Missiles* missile);
    void addABS (ABS* ABS);
    void removeModel (int id);

    QString findTypeById (int id);
    Aircrafts findAircraftById (int id);
    Missiles findMissileById (int id);
    ABS findABSById (int id);

    void changeAircraftName (int id, QString name);
    void changeAircraftMaxNormalG (int id, int max_normal_G);
    void changeAircraftMaxTanG (int id, int max_tan_G);
    void changeAircraftMaxAttackAngle (int id, int max_attack_angle);
    void changeAircraftArea (int id, int area);
    void changeAircraftMaxHeight (int id, int max_height);
    void changeAircraftMaxM (int id, int max_M);

    void changeMissileName (int id, QString name);
    void changeMissileMaxNormalG (int id, int max_normal_G);
    void changeMissileMaxTanG (int id, int max_tan_G);
    void changeMissileMaxAttackAngle (int id, int max_attack_angle);
    void changeMissileArea (int id, int area);
    void changeMissileMaxHeight (int id, int max_height);
    void changeMissileMaxM (int id, int max_M);

    void changeABSName (int id, QString name);
    void changeABSMaxAttackHeight (int id, int max_attack_height);
    void changeABSMaxAttackRadius (int id, int max_attack_radius);
    void changeABSMaxDetectionHeight (int id, int max_detection_height);
    void changeABSMaxDetectionRadius (int id, int max_detection_radius);
    void changeABSMaxAttackVelocity (int id, int max_attack_velocity);
    void changeABSAttackChance (int id, int attack_chance);
    void changeABSCombatKit (int id, int combat_kit);

    //debug functions
    void showModels ();
};

#endif // DATABASECONTROLLER_H
