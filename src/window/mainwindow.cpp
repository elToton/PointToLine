/*! \file mainwindow.cpp
  * \brief MainWindow class implementation
  *
  * \author Iofinov Platon
  * \date 15.11.2021
  *
  */

#include "mainwindow.h"

#include <iostream>
#include <QtGlobal>

//========================================================================================================================================
MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{}
//========================================================================================================================================
MainWindow::~MainWindow()
{}
//========================================================================================================================================

//========================================================================================================================================
void MainWindow::SetData(const std::map<uint, QStringList>& data)
{
  for(auto iter = data.begin(); iter != data.end(); ++iter)
    {
      DataList.push_front(std::make_pair(iter->second[0].toDouble(), iter->second[1].toDouble()));
    }
}
//========================================================================================================================================

//========================================================================================================================================
void MainWindow::SetLines(const std::map<uint, QStringList>& lines, const std::map<uint, QStringList>& points)
{
  QStringList l;
  QList<std::pair<double, double>> buff;
  for(auto iter = lines.begin(); iter != lines.end(); ++iter)
    {
      for(size_t i = 0; i < iter->second.size(); ++i)
        {
          GeographicLib::GeoCoords c(points.at(iter->second[i].toUInt())[3].toDouble(), points.at(iter->second[i].toUInt())[4].toDouble());
          l = QString::fromStdString(c.UTMUPSRepresentation(5, true)).split(" ");
          buff.push_back(std::make_pair(l[1].toDouble(), l[2].toDouble()));
          l.clear();
        }
      LinesMap.emplace(std::map<uint, QList<std::pair<double, double>>>::value_type(iter->first, buff));
      buff.clear();
    }
}
//========================================================================================================================================

//========================================================================================================================================
void MainWindow::SetResult(const std::map<uint, QStringList>& res)
{
  for(auto iter = res.begin(); iter != res.end(); ++iter)
    {
      ResultList.push_front(std::make_pair(iter->second[1].toDouble(), iter->second[2].toDouble()));
    }
}
//========================================================================================================================================

//========================================================================================================================================
void MainWindow::paintEvent(QPaintEvent *event)
{
  Q_UNUSED(event);
  QPainter qp(this);
  Draw(&qp);
}
//========================================================================================================================================

//========================================================================================================================================
void MainWindow::Draw(QPainter *painter)
{
  painter->setPen(QPen(Qt::darkGreen, 1));
  for (auto it = 0; it < DataList.size() - 1; ++it)
  {
    painter->drawLine((DataList[it].first - 546400)*5, (DataList[it].second - 5822100)*5, (DataList[it+1].first - 546400)*5, (DataList[it+1].second - 5822100)*5);
  }

  painter->setPen(QPen(Qt::darkRed, 5));
  for(auto iter = LinesMap.begin(); iter != LinesMap.end(); ++iter)
  {
    for(size_t i = 0; i < iter->second.size(); ++i)
      {
        painter->drawPoint((iter->second[i].first - 546400)*5, (iter->second[i].second - 5822100)*5);
      }
  }

  painter->setPen(QPen(Qt::magenta, 1));
  for (auto it = 0; it < DataList.size() - 1; ++it)
  {
    painter->drawPoint((ResultList[it].first - 546400)*5, (ResultList[it].second - 5822100)*5);
  }

  painter->setPen(QPen(Qt::blue, 1));
  for(auto iter = LinesMap.begin(); iter != LinesMap.end(); ++iter)
  {
    for(size_t i = 0; i < iter->second.size() - 1; ++i)
      {
        painter->drawLine((iter->second[i].first - 546400)*5, (iter->second[i].second - 5822100)*5, (iter->second[i + 1].first - 546400)*5, (iter->second[i + 1].second - 5822100)*5);
      }
  }

  painter->end();
}
//========================================================================================================================================
