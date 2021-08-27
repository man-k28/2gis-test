/*
 * \file PrimaryModelDetail.h
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Prokofev S.V.
 * \date : 18.08.2021
 */
#pragma once

#include <QPersistentModelIndex>
#include <memory>

namespace _2Gis {
namespace Models {
namespace PrimaryModelDetail {

template <typename T>
class Entry final
{
public:
    using Ptr = std::shared_ptr<Entry>;
    using EntryPtr = std::shared_ptr<T>;
    using Storage = std::vector< Ptr >;

    Entry( EntryPtr entry ) noexcept
        : entry( std::move( entry ) )
    {
        assert( Entry::entry );
    }

    Entry( const Entry & other ) = delete;
    Entry & operator =( const Entry & other )
    {
        entry = other.entry;
        persistentIndex = other.persistentIndex;
        return *this;
    }
    Entry( Entry && other ) = delete;
    Entry & operator =( Entry && other ) = delete;

    void postInitialize( QPersistentModelIndex persistentIndex  ) noexcept
    {
        assert( !Entry::persistentIndex.isValid() );
        Entry::persistentIndex.swap( persistentIndex );
        assert( Entry::persistentIndex.isValid() );
    }

    const EntryPtr get() const noexcept
    {
        return entry;
    }

    const QPersistentModelIndex & getPersistentIndex() const noexcept
    {
        return persistentIndex;
    }

private:
    EntryPtr entry = nullptr;
    QPersistentModelIndex persistentIndex;
};

}
}
}
