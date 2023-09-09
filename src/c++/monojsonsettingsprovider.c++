/* ---------------------------------------------------------------------
 * Cogwheel - Application settings and config library
 * Copyright (C) 2023 whs31.
 *
 * github.com/whs31/cogwheel
 * ---------------------------------------------------------------------- */

#include "monojsonsettingsprovider.h"
#include <utility>
#include <QtCore/QFile>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QCoreApplication>

namespace Cogwheel
{
  MonoJsonSettingsProvider::MonoJsonSettingsProvider()
    : m_filepath(QCoreApplication::applicationDirPath() + "/cfg/settings.json")
    , m_fallback_file(":/json/settings.json")
  {
    qRegisterMetaType<MonoJsonSettingsProvider*>("MonoJsonSettingsProvider*");
  }

  MonoJsonSettingsProvider::MonoJsonSettingsProvider(QString filepath, QString fallback_file)
    : m_filepath(std::move(filepath))
    , m_fallback_file(std::move(fallback_file))
  {
    qRegisterMetaType<MonoJsonSettingsProvider*>("MonoJsonSettingsProvider*");
  }

  QVariant MonoJsonSettingsProvider::read(const QString& key) const noexcept
  {
    if(not m_json.count(key))
      return "INVALID";
    return m_json.at(key);
  }

  void MonoJsonSettingsProvider::write(const QString& key, const QVariant& value) noexcept
  {
    if(m_json.count(key))
      m_json[key] = value;
    else
      m_json.insert({key, value});
  }

  void MonoJsonSettingsProvider::load() noexcept
  {
    qInfo() << "[SETTINGS] Loading settings";
    QFile file(m_filepath);
    if(not file.exists())
      QFile::copy(m_fallback_file, m_filepath);
    file.setPermissions(QFileDevice::ReadUser | QFileDevice::WriteUser);

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      QByteArray jsonData = file.readAll();
      file.close();

      QJsonDocument doc = QJsonDocument::fromJson(jsonData);
      if(not doc.isNull() and doc.isObject())
      {
        QJsonObject json = doc.object();
        for(auto it = json.begin(); it != json.end(); ++it)
          m_json.insert({it.key(), it.value().toVariant()});
      }
    }
  }

  void MonoJsonSettingsProvider::save() const noexcept
  {
    qInfo() << "[SETTINGS] Saving settings";
    QByteArray data_to_save = QJsonDocument(QJsonObject::fromVariantMap(QMap<QString, QVariant>(m_json))).toJson();
    QFile::remove(m_filepath);
    QFile file(m_filepath);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
      file.write(data_to_save);
      file.close();
    }
  }
} // Cogwheel