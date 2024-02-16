#include <iostream>
#include <unistd.h>
#include "Plane.h"
#include "Missile.h"
#include "Launcher.h"

int main(int argc, char *argv[])
{


    Plane p1 = Plane(1, 0, 0, 3, 4);
    p1.add_waypoint({100.0, 100.0});


    Plane p2 = Plane(2, 30, 30, 3, 4);
    p2.add_waypoint({100.0, 100.0});
    //p1.add_waypoint({30.0, 40.0});

    //p1.add_waypoint({0.0, 0.0});

    //Missile m1 = Missile(-10, -10, 5, 4, p1);
    //Missile m2 = Missile(-100, -100, 5, 4, p1);

    Launcher l1 = Launcher(50, 50, 10, 6);

    //std::vector<Plane> planes = {p1};
    //std::vector<Missile> missiles = {m1};
    //std::vector<FlyingObject*> objects = {&p1, &m1, &m2};
    std::vector<FlyingObject*> objects = {&p1, &p2};



    double dt = 1;
    while (true){

        bool alive_exist = false;
        for(FlyingObject* object: objects) {
            if (object->is_active()) {
                alive_exist = true;
                object->update(dt);
                std::cout << object->get_coordinates().first << ' ' << object->get_coordinates().second << std::endl;
            }
        }

        for(FlyingObject* object: objects) {
            l1.monitor(object, objects);
        }

        if (!alive_exist) {
            break;
        }
        std::cout << objects.size() << std::endl;
        std::cout << std::endl;
        sleep(1);

    }
    std::cout << "Success!";
    return 0;
}
//TODO: ADD logs