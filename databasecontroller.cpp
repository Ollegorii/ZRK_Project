#include "databasecontroller.h"

DatabaseController::DatabaseController (QString filename)
{
    this -> db = QSqlDatabase::addDatabase ("QSQLITE");
    this -> db.setDatabaseName (filename);

    if (!db.open ())
    {
        qDebug () << "Error at opening database: " << db.lastError ();
    }
}

DatabaseModels::DatabaseModels () {}

DatabaseAircraft::DatabaseAircraft () {}

DatabaseMissile::DatabaseMissile () {}

DatabaseABS::DatabaseABS () {}

DatabaseAircraft DatabaseController::findAircraftById (int id)
{
    DatabaseAircraft aircraft;
    QSqlQuery query;

    query.prepare ("SELECT * FROM Aircrafts WHERE id = (:id)");
    query.bindValue (":id", id);
    if (!query.exec ())
    {
        qDebug () << "Error at query: " << query.lastError ();
    }
    else
    {
        while (query.next ())
        {
            aircraft.id = query.value (query.record().indexOf("id")).toInt();
            aircraft.name = query.value (query.record().indexOf("name")).toString();
            aircraft.area = query.value (query.record().indexOf("area")).toInt();
            aircraft.max_height = query.value (query.record().indexOf("max_height")).toInt();
            aircraft.max_M = query.value (query.record().indexOf("max_M")).toDouble();
            aircraft.cruising_speed = query.value (query.record().indexOf("cruising_speed")).toInt();
        }
    }

    return aircraft;
}

std::vector <DatabaseAircraft> DatabaseController::findAircrafts ()
{
    DatabaseAircraft aircraft;
    std::vector <DatabaseAircraft> aircrafts;
    int counter = -1;

    QSqlQuery query;

    query.prepare ("SELECT * FROM Aircrafts");
    if (!query.exec ())
    {
        qDebug () << "Error at query: " << query.lastError ();
    }
    else
    {
        while (query.next ())
        {
            counter++;
            aircrafts.push_back (aircraft);

            aircrafts [counter].id = query.value (query.record().indexOf("id")).toInt();
            aircrafts [counter].name = query.value (query.record().indexOf("name")).toString();
            aircrafts [counter].area = query.value (query.record().indexOf("area")).toInt();
            aircrafts [counter].max_height = query.value (query.record().indexOf("max_height")).toInt();
            aircrafts [counter].max_M = query.value (query.record().indexOf("max_M")).toDouble();
            aircrafts [counter].cruising_speed = query.value (query.record().indexOf("cruising_speed")).toInt();
        }
    }

    return aircrafts;
}

DatabaseMissile DatabaseController::findMissileById (int id)
{
    DatabaseMissile missile;
    QSqlQuery query;

    query.prepare ("SELECT * FROM Missiles WHERE id = (:id)");
    query.bindValue (":id", id);
    if (!query.exec ())
    {
        qDebug () << "Error at query: " << query.lastError ();
    }
    else
    {
        while (query.next ())
        {
            missile.id = query.value (query.record().indexOf("id")).toInt();
            missile.name = query.value (query.record().indexOf("name")).toString();
            missile.area = query.value (query.record().indexOf("area")).toInt();
            missile.max_height = query.value (query.record().indexOf("max_height")).toInt();
            missile.max_M = query.value (query.record().indexOf("max_M")).toDouble();
            missile.cruising_speed = query.value (query.record().indexOf("cruising_speed")).toInt();
        }
    }

    return missile;
}

std::vector <DatabaseMissile> DatabaseController::findMissiles ()
{
    DatabaseMissile missile;
    std::vector <DatabaseMissile> missiles;
    int counter = -1;

    QSqlQuery query;

    query.prepare ("SELECT * FROM Missiles");
    if (!query.exec ())
    {
        qDebug () << "Error at query: " << query.lastError ();
    }
    else
    {
        while (query.next ())
        {
            counter++;
            missiles.push_back (missile);

            missiles [counter].id = query.value (query.record().indexOf("id")).toInt();
            missiles [counter].name = query.value (query.record().indexOf("name")).toString();
            missiles [counter].area = query.value (query.record().indexOf("area")).toInt();
            missiles [counter].max_height = query.value (query.record().indexOf("max_height")).toInt();
            missiles [counter].max_M = query.value (query.record().indexOf("max_M")).toDouble();
            missiles [counter].cruising_speed = query.value (query.record().indexOf("cruising_speed")).toInt();
        }
    }

    return missiles;
}

DatabaseABS DatabaseController::findABSById (int id)
{
    DatabaseABS ABS;
    QSqlQuery query;

    query.prepare ("SELECT * FROM ABS WHERE id = (:id)");
    query.bindValue (":id", id);
    if (!query.exec ())
    {
        qDebug () << "Error at query: " << query.lastError ();
    }
    else
    {
        while (query.next ())
        {
            ABS.id = query.value (query.record().indexOf("id")).toInt();
            ABS.name = query.value (query.record().indexOf("name")).toString();
            ABS.max_attack_height = query.value (query.record().indexOf("max_attack_height")).toInt();
            ABS.max_attack_radius = query.value (query.record().indexOf("max_attack_radius")).toInt();
            ABS.max_detection_height = query.value (query.record().indexOf("max_detection_height")).toInt();
            ABS.max_detection_radius = query.value (query.record().indexOf("max_detection_radius")).toInt();
            ABS.max_attack_velocity = query.value (query.record().indexOf("max_attack_velocity")).toInt();
            ABS.attack_chance = query.value (query.record().indexOf("attack_chance")).toInt();
            ABS.combat_kit = query.value (query.record().indexOf("combat_kit")).toInt();
        }
    }

    return ABS;
}

std::vector <DatabaseABS> DatabaseController::findABS ()
{
    DatabaseABS ABS;
    std::vector <DatabaseABS> ABSs;
    int counter = -1;

    QSqlQuery query;

    query.prepare ("SELECT * FROM ABS");
    if (!query.exec ())
    {
        qDebug () << "Error at query: " << query.lastError ();
    }
    else
    {
        while (query.next ())
        {
            counter++;
            ABSs.push_back (ABS);

            ABSs [counter].id = query.value (query.record().indexOf("id")).toInt();
            ABSs [counter].name = query.value (query.record().indexOf("name")).toString();
            ABSs [counter].max_attack_height = query.value (query.record().indexOf("max_attack_height")).toInt();
            ABSs [counter].max_attack_radius = query.value (query.record().indexOf("max_attack_radius")).toInt();
            ABSs [counter].max_detection_height = query.value (query.record().indexOf("max_detection_height")).toInt();
            ABSs [counter].max_detection_radius = query.value (query.record().indexOf("max_detection_radius")).toInt();
            ABSs [counter].max_attack_velocity = query.value (query.record().indexOf("max_attack_velocity")).toInt();
            ABSs [counter].attack_chance = query.value (query.record().indexOf("attack_chance")).toInt();
            ABSs [counter].combat_kit = query.value (query.record().indexOf("combat_kit")).toInt();
        }
    }

    return ABSs;
}
