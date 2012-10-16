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


#ifndef AUDIOREQUEST_H
#define AUDIOREQUEST_H

#include <QObject>
#include <QVariant>
#include "audiofile.h"

namespace Vk
{

class VkCustomRequest;
class AudioRequest : public QObject
{
  Q_OBJECT

public:
  explicit AudioRequest(QObject* parent = 0);
  virtual ~AudioRequest();

public slots:
  /**
   * @brief Execute request.
   *
   * @return void
   **/
  virtual void exec() = 0;

signals:
  /**
   * @brief Signal emited when request is finished.
   *
   * @param result Result of request. List of audio.
   * @return void
   **/
  void finished(const QList<Vk::AudioFile>& result);
    
protected slots:
  virtual void requestFinished(QVariant result);
  
protected:
  QList<Vk::AudioFile> m_result;
  VkCustomRequest *m_request;
};
}
#endif // AUDIOREQUEST_H
