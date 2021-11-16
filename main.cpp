/*! \file main.cpp
  * \brief Point to Line Matching algorythm
  *
  * \author Iofinov Platon
  * \date 15.11.2021
  *
  */
//========================================================================================================================================

#include <QApplication>

#include <QFile>
#include <QDir>
#include <QString>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>

#include <map>
#include <iostream>
#include <iomanip>
#include <exception>
#include <cmath>

#include <GeographicLib/Geodesic.hpp>
#include <GeographicLib/GeoCoords.hpp>
#include <GeographicLib/GeodesicLine.hpp>

#include "./src/window/mainwindow.h"

//========================================================================================================================================
/*! \fn int main(int argc, char *argv[])
 * \brief Entry point.
 *
 * Execution of the program starts here.
 *
 * \param argc Number of arguments.
 * \param argv List of arguments.
 * \return
 */
int main(int argc, char *argv[])
{
  // Initializing of parameters

  QApplication a(argc, argv);
  MainWindow w;
  PointToLine algo;
  JsonParser parser;

  //========================================================================================================================================

  // Reading .json files

  std::map<uint, QStringList> Data;
  parser.ReadJson("data.json", Data);

  std::map<uint, QStringList> Points;
  parser.ReadJson("geopoints.json", Points);

  std::map<uint, QStringList> Lines;
  parser.ReadJson("geolines.json", Lines);

  //========================================================================================================================================

  // Use algorythm and write result to "result.json"

  std::map<uint, QStringList> Result = algo.Algorythm(Data, Points, Lines);
  parser.WriteJson(Result);

  //========================================================================================================================================

  // Set data for painting

  w.SetData(Data);
  w.SetLines(Lines, Points);
  w.SetResult(Result);

  //========================================================================================================================================

  // Painting fragment of map

  w.setFixedSize(800, 600);
  w.show();
  return a.exec();
}
//========================================================================================================================================
