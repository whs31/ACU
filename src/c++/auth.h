/* ---------------------------------------------------------------------
 * ACU - Application Core Utilities Library
 * Copyright (C) 2023 whs31.
 *
 * github.com/whs31/acu
 * ---------------------------------------------------------------------- */

#pragma once

#include <map>
#include <memory>
#include <QtCore/QObject>
#include "ACU/Definitions"
#include "ACU/IHasher"

using std::map;
using std::unique_ptr;

namespace ACU
{
  class Auth : public QObject
  {
    Q_OBJECT
    Q_PROPERTY(bool authorized READ authorized WRITE setAuthorized NOTIFY authorizedChanged FINAL)
    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged FINAL)

    public:
      Auth(QString path, QString fallback_path, unique_ptr<IHasher> hasher, QObject* parent = nullptr);
      ~Auth() override = default;

      [[nodiscard]] bool authorized() const;    void setAuthorized(bool);
      [[nodiscard]] QString username() const;   void setUsername(const QString&);

      invokable bool authorize(const QString& login, const QString& password);

    signals:
      void authorizedChanged();
      void usernameChanged();

    private:
      unique_ptr<IHasher> m_hasher;
      QString m_path;
      QString m_fallback_path;
      bool m_authorized;
      QString m_username;
      map<QString, QString> m_dictionary;
  };
} // ACU
