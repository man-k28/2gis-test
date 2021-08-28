/*
 * \file primarymodel.cpp
 * \copyright (C) 2021 
 * \author : Prokofev S.V.
 * \date : 18.08.2021
 */
#include "primarymodel.h"
#include <2gis-test.h>
#include <memory>
#include <QFutureWatcher>
#include <QtConcurrent/QtConcurrent>

namespace _2Gis {
namespace Models {

PrimaryModel::PrimaryModel( QObject * parent ) noexcept
    : QAbstractListModel(parent)
{

}

int PrimaryModel::rowCount( const QModelIndex & parent ) const noexcept
{
    if( parent.isValid() )
    {
        return 0;
    }
    return static_cast< int >( m_entries.size() );
}

QVariant PrimaryModel::data( const QModelIndex & index, int role ) const noexcept
{
    if( !index.isValid() )
    {
        return {};
    }
    const auto row = index.row();
    bool validation = ( row >= 0 ) && ( static_cast< typename PrimaryModelDetail::Entry<Word>::Storage::size_type >( row ) < m_entries.size() );
    if ( ! validation ) {
        assert( false );
        return {};
    }

    const auto &entry = m_entries.at( index.row() );
    const auto &word  = entry->get();

    assert(word);

    switch ( role )
    {
        default:
            assert( false );
            return {};

        case WORD_ROLE:
            return word->value();

        case COUNT_ROLE:
            return word->count();
    }
}

QHash< int, QByteArray > PrimaryModel::roleNames() const noexcept
{
    auto roles = QAbstractListModel::roleNames();
    roles.insert(WORD_ROLE, "word");
    roles.insert(COUNT_ROLE, "count");
    return roles;
}

Word::Ptr PrimaryModel::add(const QString &word, Entry::Storage &storage) noexcept
{
    if ( word.isEmpty() )
        return {};

    auto iterator = std::lower_bound(
                            storage.cbegin(), storage.cend(),
                            word,
                            []( const PrimaryModelDetail::Entry<Word>::Ptr & entry, const QString & value ) noexcept
                            {
                                return entry->get()->value() < value;
                            }
                    );
    if( iterator != storage.end() && ( *iterator )->get()->value() == word )
    {
//        qCInfo( primaryModelLogger() ) << "Duplicated word:" << word;
        (*iterator)->get()->update();
        return nullptr;
    }

    const auto position = std::distance( storage.cbegin(), iterator );
//    beginInsertRows( {}, position, position );

    iterator = storage.emplace( iterator, std::make_unique< Entry >( std::make_shared<Word>(std::move( word )) ) );
    const auto & entry = *iterator;

//    endInsertRows();

    const QPersistentModelIndex modelIndex = createIndex( position, 0 );
    entry->postInitialize( modelIndex );
    auto wordInternal = entry->get();
    connect(
            wordInternal.get(), &Word::changed,
            this, [ this, modelIndex, wordInternal ]()
            {
                assert( modelIndex.isValid() );
                emit dataChanged( modelIndex, modelIndex );
            }
    );

    assert(
            std::is_sorted(
                    storage.cbegin(), storage.cend(),
                    []( const decltype( m_entries )::value_type & lh, const decltype( m_entries )::value_type & rh ) noexcept
                    {
                        return lh->get()->value() < rh->get()->value();
                    }
             )
    );

    return wordInternal;
}

void PrimaryModel::reload(const QUrl &url, const qint32 maxWords)
{
    using ResultType = decltype( m_entries );
    using Watcher    = QFutureWatcher< ResultType >;

    const auto watcher = new Watcher( this );
    connect( watcher, &Watcher::finished, this,
             [this, watcher = QPointer< Watcher >( watcher ), maxWords]() noexcept {
                 if ( watcher )
                 {
                     beginResetModel();
                     m_entries = watcher->result();

                     std::sort(m_entries.begin(), m_entries.end(), [](const decltype( m_entries )::value_type & lh, const decltype( m_entries )::value_type & rh){
                         return lh->get()->count() > rh->get()->count();
                     });

                     if (static_cast<qint32>(m_entries.size()) > maxWords) {
                         m_entries.resize(maxWords);
                     }

                     std::sort(m_entries.begin(), m_entries.end(), [](const decltype( m_entries )::value_type & lh, const decltype( m_entries )::value_type & rh){
                         return lh->get()->value() < rh->get()->value();
                     });

                     endResetModel();
                     watcher->deleteLater();
                     emit ready();
                 }
             } );

    const auto future = QtConcurrent::run(
        [this]( const QUrl &url ) noexcept {
            return parseDictionary( url );
        },
        url );
    watcher->setFuture( future );
}

PrimaryModelDetail::Entry<Word>::Storage PrimaryModel::parseDictionary(const QUrl &url)
{
    if ( !url.isValid() ) {
        qCWarning(primaryModelLogger()) << url.errorString();
        return {};
    }

    Entry::Storage result;

    QFile inputFile(url.toLocalFile());
    if( !inputFile.open(QIODevice::ReadOnly) ) {
        qCWarning(primaryModelLogger()) << inputFile.errorString();
        return {};
    }

    QTextStream finder(&inputFile);

    while(!finder.atEnd()) {
        auto line = finder.readLine();
        auto words = line.split(" ");
        for( const auto &word : qAsConst(words) ) {
            QRegExp regExp("\\w+");
            QString replaced(word);
            replaced.replace(QRegExp("[\\W_]+"), "");
            if (!regExp.exactMatch(replaced) )
                continue;
            add(replaced.toLower(), result);
        }
        emit progress(finder.pos() * 100 / inputFile.size());
    }
    return result;
}

QJsonArray PrimaryModel::getTop15() const noexcept
{
    QJsonArray result;

    for (const auto &item : m_entries) {
        QJsonObject obj;
        obj.insert("word", item->get()->value());
        obj.insert("count", static_cast<double>(item->get()->count()));
        result.append(obj);
    }

    return result;
}

}
}
