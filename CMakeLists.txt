cmake_minimum_required(VERSION 3.5)

project(PointToLineTest LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Core)
find_package(GeographicLib REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(PointToLineTest
  ./src/main.cpp
  ./src/parser/jsonparser.cpp
  ./src/parser/jsonparser.h
  ./src/point-to-line/pointtoline.cpp
  ./src/point-to-line/pointtoline.h
  ./src/window/mainwindow.cpp
  ./src/window/mainwindow.h
)

target_link_libraries(PointToLineTest Qt5::Core Qt5::Widgets ${GeographicLib_LIBRARIES})
