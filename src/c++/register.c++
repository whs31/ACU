/* ---------------------------------------------------------------------
 * ACU - Application Core Utilities Library
 * Copyright (C) 2023 whs31.
 *
 * github.com/whs31/acu
 * ---------------------------------------------------------------------- */

#include "register.h"
#include <QtQml/qqml.h>
#include "ACU/FileDialog"

inline void initResources() { Q_INIT_RESOURCE(acu); Q_INIT_RESOURCE(acu_rc);  }

namespace ACU
{
  void registerQml() noexcept
  {
    initResources();
    qmlRegisterModule("ACU.Dialogs", 1, 0);
    qmlRegisterType<FileDialog>("ACU.Dialogs", 1, 0, "ACUFileDialogImpl");
  }
} // ACU