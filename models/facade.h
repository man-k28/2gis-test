/*
 * \file facade.h
 * \copyright (C) 2021 
 * \author : Prokofev S.V.
 * \date : 18.08.2021
 */
#pragma once

#include <QObject>
#include <QJsonArray>

namespace _2Gis {
namespace Models {

class PrimaryModel;
class ProxyModel;

class Facade final : public QObject
{
    Q_OBJECT
    Q_PROPERTY( _2Gis::Models::PrimaryModel * primaryModel READ getPrimaryModel CONSTANT )
    Q_PROPERTY( _2Gis::Models::ProxyModel * proxyModel READ getProxyModel CONSTANT )
public:
    Facade();
public slots:
    void reload(const QUrl &url, const qint32 maxWords) noexcept;
    QJsonArray getData() const noexcept;
private:
    PrimaryModel * const m_primaryModel;
    ProxyModel * const m_proxyModel;
private:
    PrimaryModel * getPrimaryModel() const noexcept;
    ProxyModel * getProxyModel() const noexcept;
};

}
}
