/*! \file pointtiline.cpp
  * \brief PointToLine class implementation
  *
  * \author Iofinov Platon
  * \date 15.11.2021
  *
  */

#include "pointtoline.h"

//========================================================================================================================================
PointToLine::PointToLine()
{}
//========================================================================================================================================
PointToLine::~PointToLine()
{}
//========================================================================================================================================

//========================================================================================================================================
double PointToLine::Distance(double length0, double length1, double length2)
{
  double p = (length0 + length1 + length2)/2;
  return (2*sqrt(p*(p - length0)*(p - length1)*(p - length2))/length0);
}
//========================================================================================================================================

//========================================================================================================================================
double PointToLine::Distance(const GeoCoords &c0, const GeoCoords &c1, const GeoCoords &c2)
{
  const Geodesic& geod = Geodesic::WGS84();

  double s01, s02, s12;
  geod.Inverse(c0.Latitude(), c0.Longitude(), c1.Latitude(), c1.Longitude(), s01);
  geod.Inverse(c0.Latitude(), c0.Longitude(), c2.Latitude(), c2.Longitude(), s02);
  geod.Inverse(c1.Latitude(), c1.Longitude(), c2.Latitude(), c2.Longitude(), s12);

  return Distance(s12, s01, s02);
}
//========================================================================================================================================

//========================================================================================================================================
GeoCoords PointToLine::Coord(const GeoCoords &c0, const GeoCoords &c1, const GeoCoords &c2, double dist)
{
  const Geodesic& geod = Geodesic::WGS84();
  double length1;


  GeodesicLine line = geod.InverseLine(c1.Latitude() , c1.Longitude(), c2.Latitude() , c2.Longitude());
  geod.Inverse(c0.Latitude(), c0.Longitude(), c1.Latitude(), c1.Longitude(), length1);

  double s = sqrt(pow(length1, 2) - pow(dist, 2));
  double lat, lon;
  line.Position(s, lat, lon);
  GeoCoords c(lat, lon);
  return c;
}
//========================================================================================================================================

//========================================================================================================================================
std::map<uint, QStringList> PointToLine::Algorythm(std::map<uint, QStringList>& Data, std::map<uint, QStringList>& Points, std::map<uint, QStringList>& Lines)
{
  Result.clear();
  for (auto it = Data.begin(); it != Data.end(); ++it)
  {
    GeoCoords point(37, "n", it->second[0].toDouble(), it->second[1].toDouble());

    double minDist = __DBL_MAX__;
    GeoCoords coords;

    for(auto iter = Lines.begin(); iter != Lines.end(); ++iter)
    {
      for(size_t i = 0; i < iter->second.size() - 1; ++i)
      {
        GeoCoords coord_1(Points.at(iter->second[i].toUInt())[3].toDouble(), Points.at(iter->second[i].toUInt())[4].toDouble());
        GeoCoords coord_2(Points.at(iter->second[i + 1].toUInt())[3].toDouble(), Points.at(iter->second[i + 1].toUInt())[4].toDouble());

        double tmpDist = Distance(point, coord_1, coord_2);
        if (tmpDist < minDist)
        {
          minDist = tmpDist;
          coords = Coord(point, coord_1, coord_2, minDist);
        }
      }
    }

    QStringList resultList = QString::fromStdString(coords.UTMUPSRepresentation(5, true)).split(" ");
    Result.emplace(std::map<uint, QStringList>::value_type(it->first, resultList));
  }
  return Result;
}
//========================================================================================================================================
