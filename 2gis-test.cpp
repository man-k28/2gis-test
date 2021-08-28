/*
 * \file application.cpp
 * \copyright (C) 2021
 * \author : Prokofev S.V.
 * \date : 18.08.2021
 */
#include "2gis-test.h"
#include <QQmlComponent>
#include <QQmlContext>
#include <QDebug>
#include "models/facade.h"
#include "models/proxymodel.h"

Q_LOGGING_CATEGORY( logger, "2gis-test" )
Q_LOGGING_CATEGORY( primaryModelLogger, "2gis-test.PrimaryModel" )

_2GisTest::_2GisTest() noexcept
    : QObject()
    , m_modelsFacade( new _2Gis::Models::Facade() )
{
    qmlRegistration();
}

_2GisTest::~_2GisTest()
{
    if (m_modelsFacade)
        m_modelsFacade->deleteLater();
}

bool _2GisTest::init() noexcept
{
    m_engine.rootContext()->setContextProperty(QStringLiteral("_2Gis_ModelsFacade"), m_modelsFacade);
    QQmlComponent component(&m_engine, QUrl(QStringLiteral("qrc:/main.qml")));
    component.create();
    if (component.isError()) {
        qCCritical(logger()) << component.errorString();
        return false;
    }
    return true;
}

void _2GisTest::qmlRegistration() noexcept
{
    qRegisterMetaType<_2Gis::Models::ProxyModel*>("_2Gis::Models::ProxyModel*");
    qRegisterMetaType<_2Gis::Models::PrimaryModel*>("_2Gis::Models::PrimaryModel*");
}
