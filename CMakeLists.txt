cmake_minimum_required(VERSION 3.16)
project(ZRK115)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(TARGET_SOURCE_DIR ${CMAKE_SOURCE_DIR})


set(CMAKE_MODULE_PATH "$ENV{QGISPATH}/cmake" ${CMAKE_MODULE_PATH})
find_package(QGIS REQUIRED)
find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Xml
        Sql
        Test
        REQUIRED)

find_library(GDAL_LIBRARY NAMES gdal PATHS /usr/lib)
message(STATUS "GDALL_LIBRARY: ${GDAL_LIBRARY}")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(ZRK115  main.cpp
                        mainwindow.cpp
                        mainwindow.h
                        mainwindow.ui
                        anotherwindow.cpp
                        anotherwindow.h
                        anotherwindow.ui
                        databasecontroller.cpp
                        databasecontroller.h
                        databasewindow.cpp
                        databasewindow.h
                        databasewindow.ui
                        models.cpp
                        models.h
                        aircraft.cpp
                        aircraft.h
                        Plane.cpp
                        Plane.h
                        FlyingObject.cpp
                        FlyingObject.h
                        Launcher.cpp
                        Launcher.h
                        Missile.cpp
                        Missile.h
                        )

target_include_directories(ZRK115 PRIVATE
                                    ${QGIS_INCLUDE_DIR}
                                    /usr/include/gdal)


target_link_libraries(ZRK115
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Xml
        Qt5::Sql
        Qt5::Test
        ${GDAL_LIBRARY}
        ${QGIS_LIBRARY}
        )
