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

#ifndef QTVK_AUDIOLISTREPLY_H
#define QTVK_AUDIOLISTREPLY_H

#include "reply.h"
#include "audio.h"

class QVariant;
namespace QtVk
{
  
  class QTVK_EXPORT AudioListReply : public Reply
  {
    Q_OBJECT
    
  public:
    explicit AudioListReply(QObject* parent = 0);
    
    QList<Audio> result() const;
    
  signals:
    void finished(const QtVk::AudioList& reply);
    
  public slots:
    void requestFinished(const QVariant& reply);
    
  private:
    struct AudioListReplyPrivate;
    AudioListReplyPrivate *d;
  };

}

#endif // QTVK_AUDIOLISTREPLY_H
