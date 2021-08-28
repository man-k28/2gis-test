/*
 * \file word.cpp
 * \copyright (C) 2021 
 * \author : Prokofev S.V.
 * \date : 18.08.2021
 */
#include "word.h"
namespace _2Gis {

Word::Word(QString value)
    : QObject()
    , m_value(std::move(value))
{

}

Word::Word(QString value, quint64 count)
    : QObject()
    , m_value(std::move(value))
    , m_count(std::move(count))
{

}

void Word::update() noexcept
{
    m_count++;
    emit changed();
}

QString Word::value() const noexcept
{
    return m_value;
}

quint64 Word::count() const noexcept
{
    return m_count;
}

}
