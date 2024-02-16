cmake_minimum_required(VERSION 3.5)
set (project ZRK115)
project(${project} LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets Core Sql REQUIRED)

set (SOURCES
    databasecontroller.cpp
    main.cpp
    databasewindow.cpp
    models.cpp
)

set (HEADERS
    databasecontroller.h
    databasewindow.h
    models.h
)

add_executable(${project}
    ${HEADERS}
    ${SOURCES}
    databasewindow.ui
)
target_link_libraries(${project} PRIVATE Qt5::Core Qt5::Sql Qt5::Widgets)
