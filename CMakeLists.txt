cmake_minimum_required(VERSION 3.5)

project(ZRK_115_clone LANGUAGES CXX)

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

add_executable(ZRK_115_clone   main.cpp
                        mainwindow.cpp
                        mainwindow.h
                        mainwindow.ui
                        databasecontroller.cpp
                        databasecontroller.h
                        databasewindow.cpp
                        databasewindow.h
                        databasewindow.ui
                        models.cpp
                        models.h
                        Plane.h
                        Plane.cpp
                        FlyingObject.h
                        FlyingObject.cpp
                        Missile.h
                        Missile.cpp
                        Launcher.cpp
                        Launcher.h
                        settingswindow.cpp
                        settingswindow.h
                        settingswindow.ui
                        loop.cpp
                        loop.h
                        )

target_include_directories(ZRK_115_clone PRIVATE
                                    ${QGIS_INCLUDE_DIR}
                                    /usr/include/gdal)


target_link_libraries(ZRK_115_clone
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Xml
        Qt5::Sql
        Qt5::Test
        ${GDAL_LIBRARY}
        ${QGIS_LIBRARY}
        )
