/*! \file mainwindow.cpp
  * \brief MainWindow class interface
  *
  * Paint fragment of map
  *
  * \author Iofinov Platon
  * \date 15.11.2021
  *
  */

//========================================================================================================================================

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtGui>

#include "./src/point-to-line/pointtoline.h"

//========================================================================================================================================

/*!
 * \brief The MainWindow class
 */
class MainWindow : public QWidget
{
public:
  /*!
   * \brief MainWindow
   * \param parent
   */
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  //========================================================================================================================================

  /*!
   * \brief SetData
   * \param dataList
   */
  void SetData(const std::map<uint, QStringList>& dataList);

  //========================================================================================================================================

  /*!
   * \brief SetResult
   * \param resultList
   */
  void SetResult(const std::map<uint, QStringList>& resultList);

  //========================================================================================================================================

  /*!
   * \brief SetLines
   * \param linesList
   * \param points
   */
  void SetLines(const std::map<uint, QStringList>& linesList, const std::map<uint, QStringList>& points);

  //========================================================================================================================================

protected:
  /*!
   * \brief Draw
   * \param qp
   */
  void Draw(QPainter *qp);

  //========================================================================================================================================

  /*!
   * \brief paintEvent
   * \param event
   */
  void paintEvent(QPaintEvent *event);

  //========================================================================================================================================

private:
  /*!
   * \brief DataList
   */
  QList<std::pair<double, double>> DataList;

  //========================================================================================================================================

  /*!
   * \brief ResultList
   */
  QList<std::pair<double, double>> ResultList;

  //========================================================================================================================================

  /*!
   * \brief LinesMap
   */
  std::map<uint, QList<std::pair<double, double>>> LinesMap;
};

#endif // MAINWINDOW_H
//========================================================================================================================================
