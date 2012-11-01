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

#include "audiogetrequest.h"

struct QtVk::AudioGetRequest::AudioGetRequestPrivate
{
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

QtVk::AudioGetRequest::AudioGetRequest(int oid, int album, int count, int offset, bool needUser, QObject* parent)
  : AudioListRequest(parent)
  , d(new AudioGetRequestPrivate)
{
  d->oid = oid;
  d->album = album;
  d->count = count;
  d->offset = offset;
  d->needUser = needUser;
}

QtVk::AudioGetRequest::AudioGetRequest(QObject* parent)
  : AudioListRequest(parent)
  , d(new AudioGetRequestPrivate)
{
  d->oid = 0;
  d->album = 0;
  d->count = 0;
  d->offset = 0;
  d->needUser = false;
}

int QtVk::AudioGetRequest::oid() const
{
  return d->oid;
}

int QtVk::AudioGetRequest::uid() const
{
  return oid();
}

int QtVk::AudioGetRequest::gid() const
{
  return -oid();
}

int QtVk::AudioGetRequest::album() const
{
  return d->album;
}

int QtVk::AudioGetRequest::count() const
{
  return d->count;
}

int QtVk::AudioGetRequest::offset() const
{
  return d->offset;
}

bool QtVk::AudioGetRequest::needUser() const
{
  return d->needUser;
}

void QtVk::AudioGetRequest::setOid(int id)
{
  d->oid = id;
}

void QtVk::AudioGetRequest::setUid(int id)
{
  setOid(id);
}

void QtVk::AudioGetRequest::setGid(int id)
{
  setOid(-id);
}

void QtVk::AudioGetRequest::setAlbum(int id)
{
  d->album = id;
}

void QtVk::AudioGetRequest::setCount(int count)
{
  d->count = count;
}

void QtVk::AudioGetRequest::setOffset(int offset)
{
  d->offset = offset;
}

void QtVk::AudioGetRequest::setNeedUser(bool need)
{
  d->needUser = need;
}
