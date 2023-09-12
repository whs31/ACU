/* ---------------------------------------------------------------------
 * ACU - Application Core Utilities Library
 * Copyright (C) 2023 whs31.
 *
 * github.com/whs31/acu
 * ---------------------------------------------------------------------- */

#include "auth.h"
#include <stdexcept>
#include <QtCore/QFile>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>

namespace ACU
{
  Auth::Auth(QString path, QString fallback_path, unique_ptr<IHasher> hasher, QObject* parent)
    : QObject(parent)
    , m_path(std::move(path))
    , m_fallback_path(std::move(fallback_path))
    , m_hasher(std::move(hasher))
    , m_authorized(false)
    , m_username(QString())
  {
    if(m_path.isEmpty() or m_fallback_path.isEmpty())
      throw std::invalid_argument("ACU.Auth.ctor: provided invalid or empty path to json");

    if(m_hasher == nullptr)
      throw std::invalid_argument("ACU.Auth.ctor: provided null hasher");

    QFile file(m_path);
    if(not file.exists())
    {
      QFile::copy(m_fallback_path, m_path);
      qDebug() << "<ACU>.Auth: File is missing, replacing";
    }
    else
      qDebug() << "<ACU>.Auth: File located";

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      QByteArray jsonData = file.readAll();
      file.close();

      QJsonDocument doc = QJsonDocument::fromJson(jsonData);
      if(not doc.isNull() and doc.isObject())
      {
        QJsonObject json = doc.object();
        for(auto it = json.begin(); it != json.end(); ++it)
        {
          m_dictionary[it.key()] = it.value().toString();
          qDebug() << "<ACU>.Auth: Found username" << it.key();
        }
      }
    }
  }

  bool Auth::authorize(const QString& login, const QString& password)
  {
    if(authorized())
    {
      qWarning() << "<ACU>.Auth: User is already authorized with username" << username();
      return true;
    }

    if(not m_dictionary.count(login))
    {
      qWarning() << "<ACU>.Auth: Incorrect login" << login;
      return false;
    }

    QString hashed = m_hasher->hash(password.toLocal8Bit());
    if(not (m_dictionary[login] == hashed))
    {
      qWarning() << "<ACU>.Auth: Incorrect password";
      return false;
    }

    this->setUsername(login);
    this->setAuthorized(true);
    qInfo() << "<ACU>.Auth: Authorized successfully with login" << username();

    return true;
  }

  bool Auth::authorized() const { return m_authorized; }
  void Auth::setAuthorized(bool x) {
    if(m_authorized == x)
      return;
    m_authorized = x;
    emit authorizedChanged();
  }

  QString Auth::username() const { return m_username; }
  void Auth::setUsername(const QString& x) {
    if(m_username == x)
      return;
    m_username = x;
    emit usernameChanged();
  }
} // ACU