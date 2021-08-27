/*
 * \file %{Cpp:License:FileName}
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Prokofev S.V.
 * \date : 18.08.2021
 */
#include <QApplication>
#include "2gis-test.h"

constexpr static auto GLOBAL_APP_NAME = "2Gis-test";

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication app(argc, argv);
    app.setOrganizationName(GLOBAL_APP_NAME);
    app.setApplicationName(GLOBAL_APP_NAME);

    _2GisTest *mainWrapper = new _2GisTest();
    QObject::connect(&app, &QApplication::aboutToQuit, mainWrapper, [&](){
        delete mainWrapper;
    }, Qt::QueuedConnection);

    if ( !mainWrapper->init() )
         QApplication::exit(-1);

    return app.exec();
}
