/*
 * \file facade.cpp
 * \copyright (C) 2021 
 * \author : Prokofev S.V.
 * \date : 18.08.2021
 */
#include "facade.h"
#include "primarymodel.h"
#include "proxymodel.h"

namespace _2Gis {
namespace Models {

Facade::Facade()
    : QObject()
    , m_primaryModel(new PrimaryModel(this))
    , m_proxyModel(new ProxyModel(m_primaryModel, this))
{
}

void Facade::reload(const QUrl &url, const qint32 maxWords) noexcept
{
    m_primaryModel->reload(url, maxWords);
}

QJsonArray Facade::getData() const noexcept
{
    return m_primaryModel->getTop15();
}

PrimaryModel *Facade::getPrimaryModel() const noexcept
{
    return m_primaryModel;
}

ProxyModel *Facade::getProxyModel() const noexcept
{
    return m_proxyModel;
}

}
}

