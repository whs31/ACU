/* ---------------------------------------------------------------------
 * Cogwheel - Application settings and config library
 * Copyright (C) 2023 whs31.
 *
 * github.com/whs31/cogwheel
 * ---------------------------------------------------------------------- */

#pragma once

#include <QtCore/QMetaType>
#include <QtCore/QVariant>
#define invokable Q_INVOKABLE

namespace Cogwheel
{
  class ISettingsProvider
  {
    Q_GADGET

    public:
      [[nodiscard]] invokable virtual QVariant read(const QString& key) const noexcept = 0;
      virtual void write(const QString& key, const QVariant& value) noexcept = 0;

      virtual void load() noexcept = 0;
      virtual void save() const noexcept = 0;
  };
} // Cogwheel

Q_DECLARE_METATYPE(Cogwheel::ISettingsProvider*)
Q_DECLARE_INTERFACE(Cogwheel::ISettingsProvider, "dummy");