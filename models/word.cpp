/*
 * \file word.cpp
 * \copyright (C) 2021 Special Technological Center Ltd
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
