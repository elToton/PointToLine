/*! \file jsonparser.cpp
  * \brief JsonParser class implementation
  *
  * \author Iofinov Platon
  * \date 15.11.2021
  *
  */

#include "jsonparser.h"

//========================================================================================================================================
JsonParser::JsonParser()
{}
//========================================================================================================================================

//========================================================================================================================================
void JsonParser::ReadJson(const QString &fileName, std::map<uint, QStringList> &data)
{
  data.clear();
  QFile file;
  file.setFileName(fileName);

  if (!file.exists()) {
    qWarning("The file does not exist!");
    return;
  }

  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    qWarning("File open error!");
    return;
  }
  QString val = file.readAll();
  file.close();

  QJsonDocument document = QJsonDocument::fromJson(val.toUtf8());

  QJsonObject json = document.object();

  for (auto i = 0; i < json.keys().size(); ++i)
  {
    data.emplace(std::make_pair(json.keys().at(i).toUInt(), json.value(json.keys().at(i)).toString().split(",")));
  }
}
//========================================================================================================================================

//========================================================================================================================================
void JsonParser::WriteJson(const std::map<uint, QStringList> &result)
{
  QFile file(QDir::currentPath() + "/result.json");
  file.resize(0);
  file.open(QIODevice::ReadWrite);

  QJsonObject json;

  for (auto it = result.begin(); it != result.end(); ++it)
  {
    json.insert(QString::number(it->first), it->second.join(","));
  }

  QJsonDocument document;
  document.setObject(json);
  file.write(document.toJson());
  file.close();
}
//========================================================================================================================================
