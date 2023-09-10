/* ---------------------------------------------------------------------
 * ACU - Application Core Utilities Library
 * Copyright (C) 2023 whs31.
 *
 * github.com/whs31/acu
 * ---------------------------------------------------------------------- */

#pragma once

#include <map>
#include "ACU/Config/ISettingsProvider"

using std::map;

namespace ACU
{
  class MonoJsonSettingsProvider : public ISettingsProvider
  {
    Q_OBJECT

    public:
      explicit MonoJsonSettingsProvider(QObject* parent = nullptr);
      MonoJsonSettingsProvider(QString filepath, QString fallback_file, QObject* parent = nullptr);

      [[nodiscard]] invokable QVariant read(const QString& key) const noexcept override;
      void write(const QString& key, const QVariant& value) noexcept override;

      void load() noexcept override;
      void save() const noexcept override;

    protected:
      QString m_filepath;
      QString m_fallback_file;
      map<QString, QVariant> m_json;
  };
} // ACU

Q_DECLARE_METATYPE(ACU::MonoJsonSettingsProvider*)