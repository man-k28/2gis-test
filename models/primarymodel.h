/*
 * \file primarymodel.h
 * \copyright (C) 2021 
 * \author : Prokofev S.V.
 * \date : 18.08.2021
 */
#pragma once
#include <QAbstractListModel>
#include "primarymodeldetail.h"
#include "word.h"
#include <QJsonArray>
#include <QElapsedTimer>

namespace _2Gis {
namespace Models {

class ProxyModel;

class PrimaryModel final : public QAbstractListModel
{
    Q_OBJECT
    friend ProxyModel;
public:
    using Entry = Models::PrimaryModelDetail::Entry< Word >;
    using TempStorage = QMap<QString, quint64>;
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
    void ready(quint64 elapsed);
    void progress(const double &value);
public:
    void reload(const QUrl &url, const qint32 maxWords = 15);
private:
    void add(const QString &word, TempStorage &storage) noexcept;
    Entry::Storage parseDictionary(const QUrl &url);
private:
    Entry::Storage m_entries;
    QElapsedTimer timer;
};
}
}
