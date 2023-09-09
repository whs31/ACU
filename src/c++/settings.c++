/* ---------------------------------------------------------------------
 * Cogwheel - Application settings and config library
 * Copyright (C) 2023 whs31.
 *
 * github.com/whs31/cogwheel
 * ---------------------------------------------------------------------- */

#include "settings.h"

namespace Cogwheel
{
  Settings* Settings::get() { static Settings instance; return &instance; }
  Settings::Settings(QObject* parent)
    : QObject(parent)
    , m_io(/* TODO */)
  {
    this->load();
  }

  ISettingsProvider* Settings::io() const { return m_io; }
  void Settings::setIo(ISettingsProvider* x) { m_io = x; emit ioChanged(); }

  void Settings::write(const QString& key, const QVariant& value) const noexcept { io()->write(key, value); }
  void Settings::save() const noexcept { io()->save(); }
  void Settings::load() noexcept { io()->load(); emit ioChanged(); }
  void Settings::revert() noexcept { this->load(); }
  QVariant Settings::read(const QString& key) const noexcept { return io()->read(key); }
} // Cogwheel