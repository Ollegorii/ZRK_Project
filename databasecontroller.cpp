    #include "databasecontroller.h"

void DatabaseController::setModelsCounter()
{
    QSqlQuery query;

    if (!query.exec ("SELECT MAX(id_model) FROM Models"))
    {
        qDebug () << "Error at query: " << query.lastError();
    }
    else
    {
        while (query.next())
        {
            this -> modelsCounter = query.value (query.record().indexOf("MAX(id_model)")).toInt();
        }
    }
}

DatabaseController::DatabaseController (QString filename)
{
    this -> db = QSqlDatabase::addDatabase ("QSQLITE");
    this -> db.setDatabaseName (filename);

    if (!db.open ())
    {
        qDebug () << "Error at opening database: " << db.lastError ();
    }
    this -> setModelsCounter();

    qDebug () << this -> modelsCounter;
}

bool DatabaseController::addModel (Models* model)
{
    QSqlQuery query;
    QString type = model -> getType ();

    query.prepare ("INSERT INTO Models (id_model, type_model) VALUES (:id, :type);");
    query.bindValue (":id", this -> modelsCounter + 1);
    query.bindValue (":type", type);

    if (!query.exec ())
    {
        qDebug () << "Error at query: " << query.lastError ();
        return 0;
    }
    else {
        this -> modelsCounter += 1;
        model -> setId (this -> modelsCounter);

        qDebug () << this -> modelsCounter;
        return 1;
    }
}

void DatabaseController::addAircraft (Aircrafts* aircraft)
{
    if (!this -> addModel(aircraft))
    {
        return;
    }

    QSqlQuery query;
    query.prepare ("INSERT INTO Aircrafts (id, name, max_normal_G, max_tan_G, max_attack_angle, area, max_height, max_M)"
                   "VALUES (:id, :name, :max_normal_G, :max_tan_G, :max_attack_angle, :area, :max_height, :max_M)");

    query.bindValue (":id", aircraft -> getId ());
    query.bindValue (":name", aircraft -> getName ());
    query.bindValue (":max_normal_G", aircraft -> getMaxNormalG ());
    query.bindValue (":max_tan_G", aircraft -> getMaxTanG ());
    query.bindValue (":max_attack_angle", aircraft -> getMaxAttackAngle ());
    query.bindValue (":area", aircraft -> getArea ());
    query.bindValue (":max_height", aircraft -> getMaxHeight ());
    query.bindValue (":max_M", aircraft -> getMaxM ());

    if (!query.exec ())
    {
        qDebug () << "Error at query: " << query.lastError ();
    }
}

void DatabaseController::addMissile (Missiles* missile)
{
    if (!this -> addModel(missile))
    {
        return;
    }

    QSqlQuery query;
    query.prepare ("INSERT INTO Missiles (id, name, max_normal_G, max_tan_G, max_attack_angle, area, max_height, max_M)"
                   "VALUES (:id, :name, :max_normal_G, :max_tan_G, :max_attack_angle, :area, :max_height, :max_M)");

    query.bindValue (":id", missile -> getId ());
    query.bindValue (":name", missile -> getName ());
    query.bindValue (":max_normal_G", missile -> getMaxNormalG ());
    query.bindValue (":max_tan_G", missile -> getMaxTanG ());
    query.bindValue (":max_attack_angle", missile -> getMaxAttackAngle ());
    query.bindValue (":area", missile -> getArea ());
    query.bindValue (":max_height", missile -> getMaxHeight ());
    query.bindValue (":max_M", missile -> getMaxM ());

    if (!query.exec ())
    {
        qDebug () << "Error at query: " << query.lastError ();
    }
}

void DatabaseController::addABS (ABS* abs)
{
    if (!this -> addModel(abs))
    {
        return;
    }

    QSqlQuery query;
    query.prepare ("INSERT INTO ABS (id, name, max_attack_height, max_attack_radius, max_detection_height, max_detection_radius, max_attack_velocity, attack_chance, combat_kit)"
                   "VALUES (:id, :name, :max_attack_height, :max_attack_radius, :max_detection_height, :max_detection_radius, :max_attack_velocity, :attack_chance, :combat_kit)");

    query.bindValue (":id", abs -> getId ());
    query.bindValue (":name", abs -> getName ());
    query.bindValue (":max_attack_height", abs -> getMaxAttackHeight() );
    query.bindValue (":max_attack_radius", abs -> getMaxAttackRadius ());
    query.bindValue (":max_detection_height", abs -> getMaxDetectionHeight ());
    query.bindValue (":max_detection_radius", abs -> getMaxDetectionRadius ());
    query.bindValue (":max_attack_velocity", abs -> getMaxAttackVelocity ());
    query.bindValue (":attack_chance", abs -> getAttackChance ());
    query.bindValue (":combat_kit", abs -> getCombatKit ());

    if (!query.exec ())
    {
        qDebug () << "Error at query: " << query.lastError ();
    }
}

QString DatabaseController::findTypeById (int id)
{
    QSqlQuery query;
    query.prepare ("SELECT type_model FROM Models WHERE id_model = (:id)");
    query.bindValue (":id", id);

    QString type = "EMPTY";

    if (!query.exec ())
    {
        qDebug () << "Error at query: " << query.lastError ();
        return "";
    }
    else
    {
        while (query.next ())
        {
            type = query.value (query.record ().indexOf ("type_model")).toString ();
        }
    }

    return type;
}

void DatabaseController::removeModel (int id)
{
    QSqlQuery query;
    QString type = this -> findTypeById (id);

    if (type == "" || type == "EMPTY") return;

    query.prepare ("DELETE FROM Models WHERE id_model = (:id)");
    query.bindValue (":id", id);

    if (!query.exec ())
    {
        qDebug () << "Error at query: " << query.lastError ();
        return;
    }

    if (type == "Aircraft") query.prepare ("DELETE FROM Aircrafts WHERE id = (:id)");
    else if (type == "Missile") query.prepare ("DELETE FROM Missiles WHERE id = (:id)");
    else if (type == "ABS") query.prepare ("DELETE FROM ABS WHERE id = (:id)");

    query.bindValue (":id", id);

    if (!query.exec ())
    {
        qDebug () << "Error at query: " << query.lastError ();
    }
}

Aircrafts DatabaseController::findAircraftById (int id)
{
    QSqlQuery query;
    Aircrafts model;

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
            model = Aircrafts (query.value (query.record().indexOf("name")).toString(),
                        query.value (query.record().indexOf("max_normal_G")).toInt(),
                        query.value (query.record().indexOf("max_tan_G")).toInt(),
                        query.value (query.record().indexOf("max_attack_angle")).toInt(),
                        query.value (query.record().indexOf("area")).toInt(),
                        query.value (query.record().indexOf("max_height")).toInt(),
                        query.value (query.record().indexOf("max_M")).toDouble());
            model.setId(id);
            model.setType("Aircraft");
        }
    }

    return model;
}

Missiles DatabaseController::findMissileById (int id)
{
    QSqlQuery query;
    Missiles model;

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
            model = Missiles (query.value (query.record().indexOf("name")).toString(),
                        query.value (query.record().indexOf("max_normal_G")).toInt(),
                        query.value (query.record().indexOf("max_tan_G")).toInt(),
                        query.value (query.record().indexOf("max_attack_angle")).toInt(),
                        query.value (query.record().indexOf("area")).toInt(),
                        query.value (query.record().indexOf("max_height")).toInt(),
                        query.value (query.record().indexOf("max_M")).toDouble());
            model.setId(id);
            model.setType("Missile");
        }
    }

    return model;
}

ABS DatabaseController::findABSById (int id)
{
    QSqlQuery query;
    ABS model;

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
            model = ABS (query.value (query.record().indexOf("name")).toString(),
                        query.value (query.record().indexOf("max_attack_height")).toInt(),
                        query.value (query.record().indexOf("max_attack_radius")).toInt(),
                        query.value (query.record().indexOf("max_detection_height")).toInt(),
                        query.value (query.record().indexOf("max_detection_radius")).toInt(),
                        query.value (query.record().indexOf("max_attack_velocity")).toInt(),
                        query.value (query.record().indexOf("attack_chance")).toInt(),
                        query.value (query.record().indexOf("combat_kit")).toInt());
            model.setId(id);
            model.setType("ABS");
        }
    }

    return model;
}

void DatabaseController::changeAircraftName (int id, QString name)
{
    QSqlQuery query;
    query.prepare ("UPDATE Aircrafts SET name = :name WHERE id = :id;");
    query.bindValue (":id", id);
    query.bindValue (":name", name);

    if (!query.exec ()) qDebug () << "Error at query: " << query.lastError ();
}

void DatabaseController::changeAircraftMaxNormalG (int id, int max_normal_G)
{
    QSqlQuery query;
    query.prepare ("UPDATE Aircrafts SET max_normal_G = :max_normal_G WHERE id = :id;");
    query.bindValue (":id", id);
    query.bindValue (":max_normal_G", max_normal_G);

    if (!query.exec ()) qDebug () << "Error at query: " << query.lastError ();
}

void DatabaseController::changeAircraftMaxTanG (int id, int max_tan_G)
{
    QSqlQuery query;
    query.prepare ("UPDATE Aircrafts SET max_tan_G = :max_tan_G WHERE id = :id;");
    query.bindValue (":id", id);
    query.bindValue (":max_tan_G", max_tan_G);

    if (!query.exec ()) qDebug () << "Error at query: " << query.lastError ();
}

void DatabaseController::changeAircraftMaxAttackAngle (int id, int max_attack_angle)
{
    QSqlQuery query;
    query.prepare ("UPDATE Aircrafts SET max_attack_angle = :max_attack_angle WHERE id = :id;");
    query.bindValue (":id", id);
    query.bindValue (":max_attack_angle", max_attack_angle);

    if (!query.exec ()) qDebug () << "Error at query: " << query.lastError ();
}

void DatabaseController::changeAircraftArea (int id, int area)
{
    QSqlQuery query;
    query.prepare ("UPDATE Aircrafts SET area = :area WHERE id = :id;");
    query.bindValue (":id", id);
    query.bindValue (":area", area);

    if (!query.exec ()) qDebug () << "Error at query: " << query.lastError ();
}

void DatabaseController::changeAircraftMaxHeight (int id, int max_height)
{
    QSqlQuery query;
    query.prepare ("UPDATE Aircrafts SET max_height = :max_height WHERE id = :id;");
    query.bindValue (":id", id);
    query.bindValue (":max_height", max_height);

    if (!query.exec ()) qDebug () << "Error at query: " << query.lastError ();
}

void DatabaseController::changeAircraftMaxM (int id, int max_M)
{
    QSqlQuery query;
    query.prepare ("UPDATE Aircrafts SET max_M = :max_M WHERE id = :id;");
    query.bindValue (":id", id);
    query.bindValue (":max_M", max_M);

    if (!query.exec ()) qDebug () << "Error at query: " << query.lastError ();
}

void DatabaseController::changeMissileName (int id, QString name)
{
    QSqlQuery query;
    query.prepare ("UPDATE Missile SET name = :name WHERE id = :id;");
    query.bindValue (":id", id);
    query.bindValue (":name", name);

    if (!query.exec ()) qDebug () << "Error at query: " << query.lastError ();
}

void DatabaseController::changeMissileMaxNormalG (int id, int max_normal_G)
{
    QSqlQuery query;
    query.prepare ("UPDATE Missile SET max_normal_G = :max_normal_G WHERE id = :id;");
    query.bindValue (":id", id);
    query.bindValue (":max_normal_G", max_normal_G);

    if (!query.exec ()) qDebug () << "Error at query: " << query.lastError ();
}

void DatabaseController::changeMissileMaxTanG (int id, int max_tan_G)
{
    QSqlQuery query;
    query.prepare ("UPDATE Missile SET max_tan_G = :max_tan_G WHERE id = :id;");
    query.bindValue (":id", id);
    query.bindValue (":max_tan_G", max_tan_G);

    if (!query.exec ()) qDebug () << "Error at query: " << query.lastError ();
}

void DatabaseController::changeMissileMaxAttackAngle (int id, int max_attack_angle)
{
    QSqlQuery query;
    query.prepare ("UPDATE Missile SET max_attack_angle = :max_attack_angle WHERE id = :id;");
    query.bindValue (":id", id);
    query.bindValue (":max_attack_angle", max_attack_angle);

    if (!query.exec ()) qDebug () << "Error at query: " << query.lastError ();
}

void DatabaseController::changeMissileArea (int id, int area)
{
    QSqlQuery query;
    query.prepare ("UPDATE Missile SET area = :area WHERE id = :id;");
    query.bindValue (":id", id);
    query.bindValue (":area", area);

    if (!query.exec ()) qDebug () << "Error at query: " << query.lastError ();
}

void DatabaseController::changeMissileMaxHeight (int id, int max_height)
{
    QSqlQuery query;
    query.prepare ("UPDATE Missile SET max_height = :max_height WHERE id = :id;");
    query.bindValue (":id", id);
    query.bindValue (":max_height", max_height);

    if (!query.exec ()) qDebug () << "Error at query: " << query.lastError ();
}

void DatabaseController::changeMissileMaxM (int id, int max_M)
{
    QSqlQuery query;
    query.prepare ("UPDATE Missile SET max_M = :max_M WHERE id = :id;");
    query.bindValue (":id", id);
    query.bindValue (":max_M", max_M);

    if (!query.exec ()) qDebug () << "Error at query: " << query.lastError ();
}

void DatabaseController::changeABSName (int id, QString name)
{
    QSqlQuery query;
    query.prepare ("UPDATE ABS SET name = :name WHERE id = :id;");
    query.bindValue (":id", id);
    query.bindValue (":name", name);

    if (!query.exec ()) qDebug () << "Error at query: " << query.lastError ();
}

void DatabaseController::changeABSMaxAttackHeight (int id, int max_attack_height)
{
    QSqlQuery query;
    query.prepare ("UPDATE ABS SET max_attack_height = :max_attack_height WHERE id = :id;");
    query.bindValue (":id", id);
    query.bindValue (":max_attack_height", max_attack_height);

    if (!query.exec ()) qDebug () << "Error at query: " << query.lastError ();
}

void DatabaseController::changeABSMaxAttackRadius (int id, int max_attack_radius)
{
    QSqlQuery query;
    query.prepare ("UPDATE ABS SET max_attack_radius = :max_attack_radius WHERE id = :id;");
    query.bindValue (":id", id);
    query.bindValue (":max_attack_radius", max_attack_radius);

    if (!query.exec ()) qDebug () << "Error at query: " << query.lastError ();
}

void DatabaseController::changeABSMaxDetectionHeight (int id, int max_detection_height)
{
    QSqlQuery query;
    query.prepare ("UPDATE ABS SET max_detection_height = :max_detection_height WHERE id = :id;");
    query.bindValue (":id", id);
    query.bindValue (":max_detection_height", max_detection_height);

    if (!query.exec ()) qDebug () << "Error at query: " << query.lastError ();
}

void DatabaseController::changeABSMaxDetectionRadius (int id, int max_detection_radius)
{
    QSqlQuery query;
    query.prepare ("UPDATE ABS SET max_detection_radius = :max_detection_radius WHERE id = :id;");
    query.bindValue (":id", id);
    query.bindValue (":max_detection_radius", max_detection_radius);

    if (!query.exec ()) qDebug () << "Error at query: " << query.lastError ();
}

void DatabaseController::changeABSMaxAttackVelocity (int id, int max_attack_velocity)
{
    QSqlQuery query;
    query.prepare ("UPDATE ABS SET max_attack_velocity = :max_attack_velocity WHERE id = :id;");
    query.bindValue (":id", id);
    query.bindValue (":max_attack_velocity", max_attack_velocity);

    if (!query.exec ()) qDebug () << "Error at query: " << query.lastError ();
}

void DatabaseController::changeABSAttackChance (int id, int attack_chance)
{
    QSqlQuery query;
    query.prepare ("UPDATE ABS SET attack_chance = :attack_chance WHERE id = :id;");
    query.bindValue (":id", id);
    query.bindValue (":attack_chance", attack_chance);

    if (!query.exec ()) qDebug () << "Error at query: " << query.lastError ();
}

void DatabaseController::changeABSCombatKit (int id, int combat_kit)
{
    QSqlQuery query;
    query.prepare ("UPDATE ABS SET combat_kit = :combat_kit WHERE id = :id;");
    query.bindValue (":id", id);
    query.bindValue (":combat_kit", combat_kit);

    if (!query.exec ()) qDebug () << "Error at query: " << query.lastError ();
}

void DatabaseController::showModels ()
{
    QSqlQuery query;

    if (!query.exec ("SELECT * FROM Models"))
    {
        qDebug () << "Error at query: " << query.lastError ();
    }
    else
    {
        while (query.next ())
        {
            qDebug () << "Model id: " << query.value (query.record ().indexOf ("id_model")).toInt ();
            qDebug () << "Model type: " << query.value (query.record ().indexOf("type_model")).toString ();
        }
    }
}
