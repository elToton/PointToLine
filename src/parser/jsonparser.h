/*! \file jsonparser.cpp
  * \brief JsonParser class interface
  *
  * Read and Write .json files
  *
  * \author Iofinov Platon
  * \date 15.11.2021
  *
  */

//========================================================================================================================================
#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QFile>
#include <QDir>
#include <QString>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

//========================================================================================================================================
/*!
 * \brief The JsonParser class
 */
class JsonParser
{
public:
  /*!
   * \brief JsonParser
   */
  JsonParser();

  //========================================================================================================================================

  /*!
   * \brief ReadJson
   * \param fileName
   * \param data
   */
  void ReadJson(const QString& fileName, std::map<uint, QStringList>& data);

  //========================================================================================================================================

  /*!
   * \brief WriteJson
   * \param result
   */
  void WriteJson(const std::map<uint, QStringList>& result);
};

#endif // JSONPARSER_H
//========================================================================================================================================
