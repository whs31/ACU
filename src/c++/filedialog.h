/* ---------------------------------------------------------------------
 * ACU - Application Core Utilities Library
 * Copyright (C) 2023 whs31.
 *
 * github.com/whs31/acu
 * ---------------------------------------------------------------------- */

#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QFileSystemModel>
#include "ACU/Definitions"

namespace ACU
{
  class FileDialog : public QObject
  {
    Q_OBJECT
    Q_PROPERTY(QFileSystemModel* model READ model CONSTANT)

    public:
      explicit FileDialog(QObject* parent = nullptr);

      [[nodiscard]] QFileSystemModel* model() const;

    private:
      QFileSystemModel* m_model;
  };
} // ACU
