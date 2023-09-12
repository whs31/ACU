/* ---------------------------------------------------------------------
 * ACU - Application Core Utilities Library
 * Copyright (C) 2023 whs31.
 *
 * github.com/whs31/acu
 * ---------------------------------------------------------------------- */

#include "filedialog.h"
#include <cmath>
#include <array>
#include <QtCore/QDir>
#include <QtCore/QCoreApplication>
#define in :

using std::array;

namespace ACU
{
  map<QString, QString> FileDialog::IconDictionary = {
    {"folder", "qrc:/acu/icons/folder.svg"},
    {"file", "qrc:/acu/icons/file.svg"}
  };
  FileDialog::FileDialog(QObject* parent)
    : QAbstractListModel(parent)
  {
    this->setPath(QCoreApplication::applicationDirPath());
  }

  QHash<int, QByteArray> FileDialog::roleNames() const
  {
    auto roles = QAbstractItemModel::roleNames();
    roles[Index] = "index";
    roles[IsDirectory] = "isDirectory";
    roles[Name] = "name";
    roles[Size] = "size";
    roles[LastChanged] = "lastChanged";
    roles[Extension] = "extension";
    roles[Icon] = "iconPath";
    return roles;
  }

  int FileDialog::rowCount(const QModelIndex&) const { return static_cast<int>(m_storage.size()); }

  QVariant FileDialog::data(const QModelIndex& index, int role) const
  {
    if(not index.isValid())
      return {};
    switch(role)
    {
      case Index: return index.row();
      case IsDirectory: return QVariant::fromValue(m_storage[index.row()].is_directory);
      case Name: return QVariant::fromValue(m_storage[index.row()].name);
      case Size: return QVariant::fromValue(m_storage[index.row()].size);
      case LastChanged: return QVariant::fromValue(m_storage[index.row()].last_changed);
      case Extension: return QVariant::fromValue(m_storage[index.row()].extension);
      case Icon: return QVariant::fromValue(m_storage[index.row()].icon);

      default: return MODEL_READ_ERROR;
    }
  }

  QString FileDialog::path() const { return m_path; }
  void FileDialog::setPath(const QString& x)
  {
    m_storage.clear();
    QDir dir(x, "*", QDir::DirsFirst | QDir::Name | QDir::IgnoreCase, QDir::Files | QDir::Hidden | QDir::Dirs | QDir::NoDotAndDotDot);

    for(const QFileInfo& item in dir.entryInfoList())
    {
      beginInsertRows(QModelIndex(), rowCount(), rowCount());
      bool is_hidden = item.completeBaseName().isEmpty();
      if(item.isDir())
      {
        m_storage.emplace_back(true, item.fileName(), QString::number(QDir(item.filePath()).count()) + " files",
                               item.lastModified(), "");
        continue;
      }
      m_storage.emplace_back(false, item.fileName(), parseSize(item.size()),
                             item.lastModified(), is_hidden ? "" : item.suffix());
      endInsertRows();
    }
  }

  QString FileDialog::parseSize(uint64_t size)
  {
    array<QString, 7> prefixes = {
        " bit",
        " B",
        " KB",
        " MB",
        " GB",
        " TB",
        " PB"
    };

    if(size < 1024)
      return QString::number(size) + prefixes[1];
    if((double)size < std::pow(1024, 2))
      return QString::number(static_cast<float>(size) / 1024, 'f', 2) + prefixes[2];
    if((double)size < std::pow(1024, 3))
      return QString::number(static_cast<float>(size) / std::pow(1024, 2), 'f', 2) + prefixes[3];
    if((double)size < std::pow(1024, 4))
      return QString::number(static_cast<float>(size) / std::pow(1024, 3), 'f', 2) + prefixes[4];
    if((double)size < std::pow(1024, 5))
      return QString::number(static_cast<float>(size) / std::pow(1024, 4), 'f', 2) + prefixes[5];
    return {};
  }

  FileDialog::FileEntry::FileEntry()
    : is_directory(false)
    , name("invalid")
    , size("0 B")
    , last_changed(QDateTime())
    , extension("file")
  {
    if(is_directory)
      icon = FileDialog::IconDictionary["folder"];
    else
      icon = FileDialog::IconDictionary["file"];
  }

  FileDialog::FileEntry::FileEntry(bool is_directory, QString name, QString size,
                                   QDateTime last_changed, QString extension)
    : is_directory(is_directory)
    , name(std::move(name))
    , size(std::move(size))
    , last_changed(std::move(last_changed))
    , extension(std::move(extension))
  {
    if(is_directory)
      icon = FileDialog::IconDictionary["folder"];
    else
      icon = FileDialog::IconDictionary["file"];
  }
} // ACU