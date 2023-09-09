/* ---------------------------------------------------------------------
 * Cogwheel - Application settings and config library
 * Copyright (C) 2023 whs31.
 *
 * github.com/whs31/cogwheel
 * ---------------------------------------------------------------------- */

#pragma once

#include <QtCore/QObject>
#include <QtCore/QVariant>
#include "Cogwheel/ISettingsProvider"

namespace Cogwheel
{
  class Settings : public QObject
  {
    Q_OBJECT
    Q_PROPERTY(ISettingsProvider* io READ io WRITE setIo NOTIFY ioChanged)

    public:
      static Settings* get(ISettingsProvider* provider);
      ~Settings() override = default;

      [[nodiscard]] ISettingsProvider* io() const;    void setIo(ISettingsProvider*);

      invokable void write(const QString& key, const QVariant& value) const noexcept;
      invokable void save() const noexcept;
      invokable void load() noexcept;
      invokable void revert() noexcept;

      template<typename T>
      [[nodiscard]] T read(const QString& key) const noexcept { return read(key).value<T>(); }
      [[nodiscard]] QVariant read(const QString& key) const noexcept;

    signals:
      void ioChanged();

    private:
      explicit Settings(ISettingsProvider* provider, QObject* parent = nullptr);
      Settings(const Settings&);
      Settings& operator=(const Settings&);

    private:
      ISettingsProvider* m_io;
  };
} // Cogwheel