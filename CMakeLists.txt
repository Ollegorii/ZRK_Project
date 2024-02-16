cmake_minimum_required(VERSION 3.14)

project(ZRK115 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

add_executable(ZRK115
  main.cpp
        Plane.h Plane.cpp FlyingObject.cpp FlyingObject.h Plane.cpp Plane.h FlyingObject.cpp Missile.cpp Missile.h Launcher.cpp Launcher.h)
target_link_libraries(ZRK115 Qt${QT_VERSION_MAJOR}::Core)
