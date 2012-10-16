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
#ifndef GET_H
#define GET_H

#include "../audiorequest.h"

#include <QList>
#include <QVariant>

namespace Vk
{
  namespace Audio
  {
    /**
     * @brief Implementation of audio.get request.
     **/
    class Get : public AudioRequest
    {
      Q_OBJECT
      
    public:
      /**
       * @brief Default constructor.
       *
       * @param token Vk token returnded by VkAuth::auth. Defaults to "".
       * @param oid Owner id. Defaults to 0.
       * @param album Album id. Defaults to 0.
       * @param count Count of returned audios Defaults to 0.
       * @param offset Offset of first finded audio. Defaults to 0.
       * @param needUser Return information about user. Defaults to false.
       * @param parent QObject parent. Defaults to 0.
       **/
      explicit Get(QString token = "", int oid = 0, int album = 0, int count = 0, int offset = 0, bool needUser = false, QObject *parent = 0);
      /**
       * @brief Null constructor.
       *
       * @param parent QObject parent.
       **/
      explicit Get(QObject *parent);
      virtual ~Get();

      /**
       * @brief Set Vk token.
       *
       * @param token Vk token.
       * @return void
       **/
      void setToken(QString token);
      /**
       * @brief Set owner id.
       *
       * @param id Owner id.
       * @return void
       **/
      void setOid(int id);
      /**
       * @brief Set user id.
       *
       * @param id User id.
       * @return void
       **/
      void setUid(int id);
      /**
       * @brief Set group id.
       *
       * @param id Group id.
       * @return void
       **/
      void setGid(int id);
      /**
       * @brief Set album id.
       *
       * @param id Album id.
       * @return void
       **/
      void setAlbum(int id);
      /**
       * @brief Do return information about user.
       *
       * @param need Is it
       * @return void
       **/
      void setNeedUser(bool need);
      /**
       * @brief Set count of returned audios.
       *
       * @param count Count of returned audios.
       * @return void
       **/
      void setCount(int count);
      /**
       * @brief Set offset from first finded audio.
       *
       * @param offset Offset from first finded audio.
       * @return void
       **/
      void setOffset(int offset);

    public slots:
      /**
       * @brief Execute request.
       *
       * @return void
       **/
      virtual void exec();

    private:
      struct Data;
      Data *d;
    };

  }
}
#endif // GET_H
