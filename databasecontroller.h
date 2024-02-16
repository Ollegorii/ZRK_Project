#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

#include <QtSql>
#include <vector>

class DatabaseModels
{
public:
    DatabaseModels ();

    int id;
    QString name;
};

class DatabaseAircraft : public DatabaseModels
{
public:
    DatabaseAircraft ();

    int area;
    int max_height;
    double max_M;
    int cruising_speed;
};

class DatabaseMissile : public DatabaseModels
{
public:
    DatabaseMissile ();

    int area;
    int max_height;
    double max_M;
    int cruising_speed;
};

class DatabaseABS : public DatabaseModels
{
public:
    DatabaseABS ();

    int max_attack_height;
    int max_attack_radius;
    int max_detection_height;
    int max_detection_radius;
    int max_attack_velocity;
    int attack_chance;
    int combat_kit;
};

class DatabaseController
{
public:
    QSqlDatabase db;

    DatabaseController (QString filename);

    DatabaseAircraft findAircraftById (int id);
    std::vector <DatabaseAircraft> findAircrafts ();

    DatabaseMissile findMissileById (int id);
    std::vector <DatabaseMissile> findMissiles ();

    DatabaseABS findABSById (int id);
    std::vector <DatabaseABS> findABS ();
};

#endif // DATABASECONTROLLER_H
