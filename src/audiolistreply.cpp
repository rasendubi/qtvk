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

#include "audiolistreply.h"

#include <QVariant>

struct QtVk::AudioListReply::AudioListReplyPrivate
{
  
};

QtVk::AudioListReply::AudioListReply(QObject* parent)
  : Reply(parent)
  , d(new AudioListReplyPrivate)
{

}

void QtVk::AudioListReply::requestFinished(const QVariant& reply)
{
  QVariantList var = reply.toMap()["response"].toList();
  QList<Audio> result;
  foreach( QVariant audio, var )
  {
    QVariantMap mp = audio.toMap();
    if( !mp.isEmpty() )
    {
      Audio a;
      a.aid = mp.value("aid").toInt();
      a.oid = mp.value("owner_id").toInt();
      a.artist = encode(mp.value("artist").toString()).trimmed();
      a.title = encode(mp.value("title").toString()).trimmed();
      a.duration = mp.value("duration").toInt();
      a.url = mp.value("url").toUrl();
      a.lyricsId = mp.value("lyrics_id", "").toInt();
      a.album = mp.value("album", QVariant(0)).toInt();
      result.push_back(a);
    }
  }
  emit finished(result);
}

