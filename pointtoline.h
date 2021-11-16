/*! \file pointtiline.h
  * \brief PointToLine class interface
  *
  * Use Point to match algorythm
  *
  * \author Iofinov Platon
  * \date 15.11.2021
  *
  */

//========================================================================================================================================

#ifndef POINTTOLINE_H
#define POINTTOLINE_H

#include "./src/parser/jsonparser.h"

#include <map>
#include <iostream>
#include <iomanip>
#include <exception>
#include <cmath>

#include <GeographicLib/Geodesic.hpp>
#include <GeographicLib/GeoCoords.hpp>
#include <GeographicLib/GeodesicLine.hpp>

using namespace GeographicLib;

//========================================================================================================================================
/*!
 * \brief The PointToLine class
 */
class PointToLine
{
public:
  /*!
   * \brief PointToLine
   */
  PointToLine();
  ~PointToLine();

  //========================================================================================================================================

  /*!
   * \brief Algorythm
   * \param Data
   * \param Points
   * \param Lines
   * \return
   */
  std::map<uint, QStringList> Algorythm(std::map<uint, QStringList>& Data, std::map<uint, QStringList>& Points, std::map<uint, QStringList>& Lines);

  //========================================================================================================================================

private:
  /*!
   * \brief Result
   */
  std::map<uint, QStringList> Result;

  //========================================================================================================================================

  /*!
   * \brief Distance
   * \param length0
   * \param length1
   * \param length2
   * \return
   */
  double Distance(double length0, double length1, double length2);
  /*!
   * \brief Distance
   * \param c0
   * \param c1
   * \param c2
   * \return
   */
  double Distance(const GeoCoords &c0, const GeoCoords &c1, const GeoCoords &c2);

  //========================================================================================================================================

  /*!
   * \brief Coord
   * \param c0
   * \param c1
   * \param c2
   * \param dist
   * \return
   */
  GeoCoords Coord(const GeoCoords& c0, const GeoCoords& c1, const GeoCoords& c2, double dist);
};

#endif // POINTTOLINE_H
//========================================================================================================================================
