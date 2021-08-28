/*
 * \file word.h
 * \copyright (C) 2021 
 * \author : Prokofev S.V.
 * \date : 18.08.2021
 */
#pragma once
#include <QObject>
#include <QString>
#include <memory>

namespace _2Gis {

class Word final : public QObject
{
    Q_OBJECT
public:
    using Ptr = std::shared_ptr< Word >;
    using ConstPtr = std::shared_ptr< const Word >;
public:
    explicit Word(QString value);
    void update() noexcept;
public:
    QString value() const noexcept;
    quint64 count() const noexcept;
signals:
    void changed();
private:
    QString m_value;
    quint64 m_count = 1;
};

}
