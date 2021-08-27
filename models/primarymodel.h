/*
 * \file primarymodel.h
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Prokofev S.V.
 * \date : 18.08.2021
 */
#pragma once
#include <QAbstractListModel>
#include "primarymodeldetail.h"
#include "word.h"
#include <QJsonArray>

namespace _2Gis {
namespace Models {

class ProxyModel;

class PrimaryModel final : public QAbstractListModel
{
    Q_OBJECT
    friend ProxyModel;
public:
    using Entry = Models::PrimaryModelDetail::Entry< Word >;

    enum Role
    {
        WORD_ROLE = Qt::UserRole + 1,
        COUNT_ROLE
    };

    explicit PrimaryModel( QObject * parent ) noexcept;
private:
    int rowCount( const QModelIndex & parent ) const noexcept override;
    QVariant data( const QModelIndex & index, int role ) const noexcept override;
    QHash< int, QByteArray > roleNames() const noexcept override;
public:
    QJsonArray getTop15() const noexcept;
signals:
    void ready();
    void progress(const double &value);
public:
    Word::Ptr add(const QString &word, Entry::Storage &storage) noexcept;
    void reload(const QUrl &url, const qint32 maxWords = 15);
private:
    Entry::Storage parseDictionary(const QUrl &url);
private:
    Entry::Storage m_entries;
};
}
}
