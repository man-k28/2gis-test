/*
 * \file proxymodel.h
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Prokofev S.V.
 * \date : 18.08.2021
 */
#pragma once
#include <QSortFilterProxyModel>
#include "primarymodel.h"

namespace _2Gis {
namespace Models {

class ProxyModel final : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit ProxyModel( PrimaryModel * primaryModel, QObject * parent  ) noexcept;
private:
    bool filterAcceptsRow( int primaryRow, const QModelIndex & primaryParent ) const override;
    bool lessThan( const QModelIndex & primaryLeft, const QModelIndex & primaryRight ) const override;
private:
    PrimaryModel * const m_primaryModel;
};

}
}
