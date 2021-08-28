/*
 * \file application.h
 * \copyright (C) 2021 
 * \author : Prokofev S.V.
 * \date : 18.08.2021
 */
#pragma once
#include <QQmlApplicationEngine>
#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY( logger )
Q_DECLARE_LOGGING_CATEGORY( primaryModelLogger )

namespace _2Gis {
namespace Models {
class Facade;
}
}

class _2GisTest final : public QObject
{
    Q_OBJECT
public:
    _2GisTest() noexcept;
    ~_2GisTest();

    bool init() noexcept;
private:
    void qmlRegistration() noexcept;

    QQmlApplicationEngine m_engine;
    _2Gis::Models::Facade * const m_modelsFacade;
};

