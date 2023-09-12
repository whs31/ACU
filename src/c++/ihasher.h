/* ---------------------------------------------------------------------
 * ACU - Application Core Utilities Library
 * Copyright (C) 2023 whs31.
 *
 * github.com/whs31/acu
 * ---------------------------------------------------------------------- */

#pragma once

#include <QtCore/QString>

namespace ACU
{
  class IHasher
  {
    public:
      [[nodiscard]] virtual QByteArray hash(const QByteArray& data) const = 0;
      virtual ~IHasher() = default;

      //static char* strData(const QString&) noexcept;
      //static const char* strCData(const QString&) noexcept;
  };
} // ACU

namespace ACU
{
  //char* IHasher::strData(const QString& str) noexcept { return str.toLocal8Bit().data(); }
  //const char* IHasher::strCData(const QString& str) noexcept { return str.toLocal8Bit().constData(); }
} // ACU