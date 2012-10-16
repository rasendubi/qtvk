/*
 *    QtVk. Qt interface for vk.com API
 *    Copyright (C) 2012  Alexey Shmalko <dubi.rasen@gmail.com>
 * 
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License as published by the Free Software Foundation; either
 *    version 2.1 of the License, or (at your option) any later version.
 * 
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 * 
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */


#include "search.h"
#include "src/audio/audiotools.h"
#include "src/vkcustomrequest.h"

#ifndef QT_NO_DEBUG
  #include <QDebug>
#endif

struct Vk::Audio::Search::Data
{
  QString token, query;
  bool autoComplete, lyrics;
  int sort, count, offset;
};

Vk::Audio::Search::Search(const QString& token, const QString& q, bool autoComplete, bool withLyrics, int count, int offset, int sort, QObject* parent): 
  AudioRequest(parent)
{
  d = new Data;
  d->token = token;
  d->query = q;
  d->autoComplete = autoComplete;
  d->lyrics = withLyrics;
  d->count = count;
  d->offset = offset;
  d->sort = sort;
}

Vk::Audio::Search::Search(QObject* parent): 
  AudioRequest(parent)
{
  d = new Data;
  d->autoComplete = true;
  d->lyrics = false;
  d->count = 0;
  d->offset = 0;
  d->sort = 2;
}

Vk::Audio::Search::~Search()
{
  delete d;
}

void Vk::Audio::Search::setAutoComplete(bool autoComplete)
{
  d->autoComplete = autoComplete;
}

void Vk::Audio::Search::setCount(int count)
{
  d->count = count;
}

void Vk::Audio::Search::setOffset(int offset)
{
  d->offset = offset;
}

void Vk::Audio::Search::setQuery(const QString& query)
{
  d->query = query;
}

void Vk::Audio::Search::setSort(int sort)
{
  d->sort = sort;
}

void Vk::Audio::Search::setWithLyrics(bool withLyrics)
{
  d->lyrics = withLyrics;
}

void Vk::Audio::Search::setToken(const QString& token)
{
  d->token = token;
}

void Vk::Audio::Search::exec()
{
  QMap<QString, QString> map;
  Q_ASSERT( !d->query.isEmpty() );
  map.insert("access_token", d->token);
  map.insert("q", d->query);
  if( d->autoComplete )
    map.insert("auto_complete", "1");
  map.insert("sort", QString::number(d->sort));
  if( d->lyrics )
    map.insert("lyrics", "1");
  if( d->count )
    map.insert("count", QString::number(d->count));
  if( d->offset )
    map.insert("offset", QString::number(d->offset));
  
  if( m_request )
  {
    m_request->deleteLater();
    m_request = 0;
  }
  
  m_request = new Vk::VkCustomRequest("audio.search", map, this);
  connect(m_request, SIGNAL(result(QVariant)), this, SLOT(requestFinished(QVariant)));
  m_request->exec();
}
