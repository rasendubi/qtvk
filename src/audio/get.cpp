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


#include "src/audio/audiotools.h"
#include "src/audio/get.h"
#include "src/tools.h"
#include "src/vkcustomrequest.h"

namespace Vk
{
namespace Audio
{
  
struct Get::Data
{
  /**
   * @brief Vk token.
   **/
  QString token;
  /**
   * @brief Owner id.
   **/
  int oid;
  /**
   * @brief Album id.
   **/
  int album;
  /**
   * @brief Count of returned audios.
   **/
  int count;
  /**
   * @brief Offset from first finded audio.
   **/
  int offset;
  /**
   * @brief Do return information about user.
   **/
  bool needUser;
  
};

Get::Get( QString token, int oid, int album, int count, int offset, bool needUser, QObject *parent )
  : AudioRequest( parent )
{
  d = new Data;
  d->token = token;
  d->oid = oid;
  d->album = album;
  d->count = count;
  d->offset = offset;
  d->needUser = needUser;
}

Get::Get(QObject* parent) 
  : AudioRequest(parent)
{
  d = new Data;
  d->token = "";
  d->oid = 0;
  d->album = 0;
  d->count = 0;
  d->offset = 0;
  d->needUser = false;
}

Get::~Get()
{
  delete d;
}

void Get::setToken(QString token)
{
  d->token = token;
}

void Get::setOid(int id)
{
  d->oid = id;
}

void Get::setUid(int id)
{
  d->oid = id;
}

void Get::setGid(int id)
{
  d->oid = -id;
}

void Get::setAlbum(int id)
{
  d->album = id;
}

void Get::setNeedUser(bool need)
{
  d->needUser = need;
}

void Get::setCount(int count)
{
  d->count = count;
}

void Get::setOffset(int offset)
{
  d->offset = offset;
}

void Get::exec()
{
  QMap<QString, QString> map;
  if( !d->token.isEmpty() )
  {
    map.insert("access_token", d->token);
    if( d->oid > 0 )
      map.insert("uid", QString::number(d->oid));
    else if( d->oid < 0 )
      map.insert("gid", QString::number(-d->oid));
    if( d->album != 0 )
      map.insert("album", QString::number(d->album));
    if( d->count > 0 )
      map.insert("count", QString::number(d->count));
    if( d->offset > 0 )
      map.insert("offset", QString::number(d->offset));
    if( d->needUser )
      map.insert("need_user", "1");
    m_request = new VkCustomRequest("audio.get", map);
    connect(m_request, SIGNAL(result(QVariant)), this, SLOT(requestFinished(QVariant)));
    m_request->exec();
  }
}

}
}