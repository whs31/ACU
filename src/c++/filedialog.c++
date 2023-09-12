/* ---------------------------------------------------------------------
 * ACU - Application Core Utilities Library
 * Copyright (C) 2023 whs31.
 *
 * github.com/whs31/acu
 * ---------------------------------------------------------------------- */

#include "filedialog.h"

namespace ACU
{
  FileDialog::FileDialog(QObject* parent)
    : QObject(parent)
    , m_model(new QFileSystemModel(this))
  {}

  QFileSystemModel* FileDialog::model() const { return m_model; }
} // ACU