/* ---------------------------------------------------------------------
 * ACU - Application Core Utilities Library
 * Copyright (C) 2023 whs31.
 *
 * github.com/whs31/acu
 * ---------------------------------------------------------------------- */

#pragma once

#include <vector>
#include <QtCore/QObject>
#include <QtCore/QAbstractListModel>
#include <QtCore/QDateTime>
#include "ACU/Definitions"

using std::vector;

namespace ACU
{
  class FileDialog : public QAbstractListModel
  {
    Q_OBJECT
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged FINAL)

    public:
      enum Roles
      {
        Index = Qt::UserRole + 1,
        IsDirectory,
        Name,
        Size,
        LastChanged,
        Extension,
        Icon
      };

      struct FileEntry
      {
        FileEntry();
        FileEntry(bool is_directory, QString name, QString size, QDateTime last_changed, QString extension);

        bool is_directory;
        QString name;
        QString size;
        QDateTime last_changed;
        QString extension;
        QString icon;
      };

      explicit FileDialog(QObject* parent = nullptr);

      [[nodiscard]] QString path() const;     void setPath(const QString&);

      [[nodiscard]] int rowCount(const QModelIndex& = QModelIndex()) const override;
      [[nodiscard]] QVariant data(const QModelIndex& index, int role) const override;

    signals:
      void pathChanged();

    protected:
      [[nodiscard]] QHash<int, QByteArray> roleNames() const override;
      static QString parseSize(uint64_t size) ;

    private:
      vector<FileEntry> m_storage;
      QString m_path;
  };
} // ACU
