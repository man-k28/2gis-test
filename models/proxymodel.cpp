/*
 * \file proxymodel.cpp
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Prokofev S.V.
 * \date : 18.08.2021
 */
#include "proxymodel.h"

namespace _2Gis {
namespace Models {

ProxyModel::ProxyModel(PrimaryModel * primaryModel, QObject * parent ) noexcept
    : QSortFilterProxyModel( parent )
    , m_primaryModel( primaryModel )
{
    setSourceModel(m_primaryModel);
    sort( 0, Qt::SortOrder::AscendingOrder );
}

bool ProxyModel::filterAcceptsRow(int primaryRow, const QModelIndex &primaryParent) const
{
    Q_UNUSED(primaryRow)
    Q_UNUSED(primaryParent)
    return true;
}

bool ProxyModel::lessThan(const QModelIndex &primaryLeft, const QModelIndex &primaryRight) const
{
    assert( primaryLeft.isValid() && primaryRight.isValid() );

    const auto & left = m_primaryModel->data( primaryLeft, PrimaryModel::WORD_ROLE);
    const auto & right = m_primaryModel->data( primaryRight, PrimaryModel::WORD_ROLE);

    const auto &leftValue = left.value< QString >();
    const auto &rightValue = right.value< QString >();

    return leftValue < rightValue;
}

}
}
