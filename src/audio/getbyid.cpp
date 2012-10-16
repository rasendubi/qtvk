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


#include "src/audio/getbyid.h"
#include "src/tools.h"
#include "src/vkcustomrequest.h"

#include <QMap>

namespace Vk
{
namespace Audio
{
  
struct GetById::Data
{
  /**
   * @brief Vk token.
   **/
  QString token;
  /**
   * @brief Requested list.
   **/
  QStringList audios;
};
  
GetById::GetById(QString token, QStringList audios, QObject* parent)
  : AudioRequest(parent)
{
  d = new Data;
  d->token = token;
  d->audios = audios;
}

GetById::GetById(QString token, QList< AudioFile > audios, QObject* parent)
  : AudioRequest(parent)
{
  d = new Data;
  d->token = token;
  foreach( Vk::AudioFile audio, audios )
    d->audios.append(QString::number(audio.oid) + "_" + QString::number(audio.aid));
}

GetById::GetById(QObject* parent): AudioRequest(parent)
{
  d = new Data;
}

GetById::~GetById()
{
  delete d;
}

void GetById::append(const QString& str)
{
  d->audios.append(str);
}

void GetById::append(const QStringList& lst)
{
  d->audios.append(lst);
}

void GetById::append(const AudioFile& audio)
{
  d->audios.append(QString::number(audio.oid) + "_" + QString::number(audio.aid));
}

void GetById::append(const QList< AudioFile > audios)
{
  foreach( Vk::AudioFile audio, audios )
    d->audios.append(QString::number(audio.oid) + "_" + QString::number(audio.aid));
}

void GetById::clear()
{
  d->audios.clear();
}

void GetById::setToken(QString token)
{
  d->token = token;
}

void GetById::exec()
{
  QMap<QString, QString> map;
  if( !d->token.isEmpty() )
  {
    map.insert("access_token", d->token);
    map.insert("audios", d->audios.join(","));
    m_request = new Vk::VkCustomRequest("audio.getById", map);
    connect(m_request, SIGNAL(result(QVariant)), this, SLOT(requestFinished(QVariant)));
    m_request->exec();    
  }
}

}
}

