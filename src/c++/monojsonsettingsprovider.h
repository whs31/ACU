/* ---------------------------------------------------------------------
 * Cogwheel - Application settings and config library
 * Copyright (C) 2023 whs31.
 *
 * github.com/whs31/cogwheel
 * ---------------------------------------------------------------------- */

#pragma once

#include <map>
#include "Cogwheel/ISettingsProvider"

using std::map;

namespace Cogwheel
{
  class MonoJsonSettingsProvider : public ISettingsProvider
  {
    Q_GADGET
    Q_INTERFACES(Cogwheel::ISettingsProvider)

    public:
      MonoJsonSettingsProvider();
      MonoJsonSettingsProvider(QString filepath, QString fallback_file);

      [[nodiscard]] invokable QVariant read(const QString& key) const noexcept override;
      void write(const QString& key, const QVariant& value) noexcept override;

      void load() noexcept override;
      void save() const noexcept override;

    protected:
      QString m_filepath;
      QString m_fallback_file;
      map<QString, QVariant> m_json;
  };
} // Cogwheel

Q_DECLARE_METATYPE(Cogwheel::MonoJsonSettingsProvider*)