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


#include "get.h"
#include "../vkcustomrequest.h"

struct Vk::Friends::Get::Data
{
  int uid, count, offset, lid;
  QString token, fields, nameCase, order;
};

Vk::Friends::Get::Get(QString token, int uid, QString fields, QString nameCase, int count, int offset, int lid, QString order, QObject* parent): 
  QObject(parent)
{
  d = new Data;
  d->uid = uid;
  d->fields = fields;
  d->nameCase = nameCase;
  d->count = count;
  d->offset = offset;
  d->lid = lid;
  d->order = order;
  d->token = token;
}

Vk::Friends::Get::Get(QObject* parent): QObject(parent)
{
  d = new Data;
  d->uid = 0;
  d->count = 0;
  d->offset = 0;
  d->lid = 0;
}

Vk::Friends::Get::~Get()
{
  delete d;
}

void Vk::Friends::Get::exec()
{
  QMap<QString, QString> map;
  if( !d->token.isEmpty() )
  {
    map.insert("access_token", d->token);
    if( d->uid )
      map.insert("uid", QString::number(d->uid));
    if( !d->fields.isEmpty() )
      map.insert("fields", d->fields);
    if( !d->nameCase.isEmpty() )
      map.insert("name_case", d->nameCase);
    if( d->count )
      map.insert("count", QString::number(d->count));
    if( d->offset )
      map.insert("offset", QString::number(d->offset));
    if( d->lid )
      map.insert("lid", QString::number(d->lid));
    if( !d->order.isEmpty() )
      map.insert("order", d->order);

    m_request = new VkCustomRequest("friends.get", map);
    connect(m_request, SIGNAL(result(QVariant)), this, SLOT(requestFinished(QVariant)));
    m_request->exec();
  }
}

void Vk::Friends::Get::requestFinished(QVariant result)
{
  QVariantList lst = result.toMap()["response"].toList();
  QList<Vk::User> users;
  if( d->fields.isEmpty() )
    foreach( QVariant var, lst )
    {
      Vk::User user;
      user.uid = var.toInt();
      users.append(user);
    } 
  else
    foreach( QVariant var, lst )
    {
      QVariantMap mp = var.toMap();
      Vk::User user;
      user.uid = mp.value("uid").toInt();
      user.firstName = mp.value("first_name", "").toString();
      user.lastName = mp.value("last_name", "").toString();
      user.nickname = mp.value("nickname", "").toString();
      user.sex = Vk::Sex(mp.value("sex", 0).toInt());
      user.online = mp.value("online", false).toBool();
      user.birthDate = mp.value("bdate", "").toString();
      user.city = mp.value("city", 0).toInt();
      user.country = mp.value("country", 0).toInt();
      user.photo = mp.value("photo", "").toUrl();
      user.photoMedium = mp.value("photo_medium", "").toUrl();
      user.photoMediumRec = mp.value("photo_medium_rec", "").toUrl();
      user.photoBig = mp.value("photo_big", "").toUrl();
      user.photoRec = mp.value("photo_rec", "").toUrl();
      user.screenName = mp.value("screen_name", "").toString();
      user.hasMobile = mp.value("has_mobile", false).toBool();
      user.rate = mp.value("rate").toInt();
      users.append(user);
    }
  emit finished(users);
}

