/* ---------------------------------------------------------------------
 * Cogwheel - Application settings and config library
 * Copyright (C) 2023 whs31.
 *
 * github.com/whs31/cogwheel
 * ---------------------------------------------------------------------- */

#include "settings.h"
#include <stdexcept>

namespace Cogwheel
{
  Settings* Settings::get(ISettingsProvider* provider) { static Settings instance(provider); return &instance; }
  Settings::Settings(ISettingsProvider* provider, QObject* parent)
    : QObject(parent)
    , m_io(provider)
  {
    if(not provider)
      throw std::invalid_argument("Cogwheel.Settings.ctor: Null provider was passed to constructor");
    this->load();
    qRegisterMetaType<ISettingsProvider*>("ISettingsProvider*");
  }

  ISettingsProvider* Settings::io() const { return m_io; }
  void Settings::setIo(ISettingsProvider* x) { m_io = x; emit ioChanged(); }

  void Settings::write(const QString& key, const QVariant& value) const noexcept { io()->write(key, value); }
  void Settings::save() const noexcept { io()->save(); }
  void Settings::load() noexcept { io()->load(); emit ioChanged(); }
  void Settings::revert() noexcept { this->load(); }
  QVariant Settings::read(const QString& key) const noexcept { return io()->read(key); }
} // Cogwheel