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

#include "getcount.h"
#include "../vkcustomrequest.h"
#include <QMap>

struct Vk::Audio::GetCount::Data
{
  QString token;
  int oid;
  
  VkCustomRequest *request;
  int result;
};

Vk::Audio::GetCount::GetCount(const QString& token, int oid, QObject* parent)
  : QObject(parent)
{
  d = new Data;
  d->token = token;
  d->oid = oid;
  d->request = 0;
  d->result = 0;
}

Vk::Audio::GetCount::GetCount(QObject* parent): QObject(parent)
{
  d = new Data;
  d->token = "";
  d->oid = 0;
  d->request = 0;
  d->result = 0;
}

Vk::Audio::GetCount::~GetCount()
{
  delete d;
}

void Vk::Audio::GetCount::setToken(const QString& token)
{
  d->token = token;
}

void Vk::Audio::GetCount::setOid(int oid)
{
  d->oid = oid;
}

void Vk::Audio::GetCount::exec()
{
  if( !d->token.isEmpty() && d->oid )
  {
    QMap<QString, QString> map;
    map.insert("access_token", d->token);
    map.insert("oid", QString::number(d->oid));
    d->request = new Vk::VkCustomRequest("audio.getCount", map, this);
    connect(d->request, SIGNAL(result(QVariant)), this, SLOT(requestFinished(QVariant)));
    d->request->exec();
  }
}

void Vk::Audio::GetCount::requestFinished(QVariant result)
{
  emit finished(result.toMap().value("response").toInt());
}
