/* ---------------------------------------------------------------------
 * ACU - Application Core Utilities Library
 * Copyright (C) 2023 whs31.
 *
 * github.com/whs31/acu
 * ---------------------------------------------------------------------- */

#pragma once

#include <QtCore/QObject>
#include <QtCore/QMetaType>
#include <QtCore/QVariant>
#define invokable Q_INVOKABLE

namespace ACU
{
  class ISettingsProvider : public QObject
  {
    Q_OBJECT

    public:
      [[nodiscard]] invokable virtual QVariant read(const QString& key) const noexcept = 0;
      virtual void write(const QString& key, const QVariant& value) noexcept = 0;

      virtual void load() noexcept = 0;
      virtual void save() const noexcept = 0;

    protected:
      explicit ISettingsProvider(QObject* parent = nullptr);
  };
} // ACU

Q_DECLARE_METATYPE(ACU::ISettingsProvider*)
Q_DECLARE_INTERFACE(ACU::ISettingsProvider, "acu");

namespace ACU
{
  inline ISettingsProvider::ISettingsProvider(QObject* parent)
      : QObject(parent)
  {}
} // ACU