#include "loop.h"

Loop::Loop()
{
}

void Loop::start()
{

    double dt = 1;
    while(true)
    {
        bool alive_exist = false;

        for(Launcher* l : launchers){
            for (FlyingObject* object : flyobjects) {
                l->monitor(object, flyobjects);
            }
        }

        for (FlyingObject* object: flyobjects) {
            if (object->is_active()){
                emit drawRadar(launchers, 4);
                alive_exist = true;
                std::pair<double, double> start = {object->get_coordinates().first, object->get_coordinates().second};
                object->update(dt);
                std::pair<double, double> finish = {object->get_coordinates().first, object->get_coordinates().second};
                double x = finish.first - start.first, y = finish.second - start.second;
                double angle = atan(y / x) / 3.1415 * 180;
                if (x < 0)
                {
                    angle += 180;
                }
                if (object->get_type() == plane)
                    emit drawPoint(start, angle);
                if (object->get_type() == missile)
                    emit drawMissilePoint(start, angle);
                if (object->get_type() == missile)
                    emit drawMissilePoint(finish, angle);
                if (object->get_type() == plane)
                    emit drawPoint(finish, angle);
                emit drawLine({start, finish});
            }
        }

        if (!alive_exist)
           break;

        QTest::qWait(300);
    }
}
