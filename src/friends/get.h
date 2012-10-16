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


#ifndef FRIENDS_GET_H
#define FRIENDS_GET_H

#include "../user.h"
#include <QObject>
#include <QVariant>

namespace Vk
{

  class VkCustomRequest;
  namespace Friends
  {
    class Get : public QObject
    {
      Q_OBJECT
    public:
      explicit Get(QString token = "", int uid = 0, QString fields = "", QString nameCase = "", int count = 0,
                   int offset = 0, int lid = 0, QString order = "hints", QObject* parent = 0);
      explicit Get(QObject* parent);
      virtual ~Get();
      
    public slots:
      /**
      * @brief Execute request.
      *
      * @return void
      **/
      void exec();

    signals:
      /**
      * @brief Signal emited when request is finished.
      *
      * @param result Result of request. List of audio.
      * @return void
      **/
      void finished(QList<Vk::User> result); 
      
    private:
      struct Data;
      Data *d;
      
    protected:
      /**
        * @brief Request.
        **/
      VkCustomRequest *m_request;
      /**
        * @brief Result of m_request.
        **/
      QList<Vk::User> m_result;

    private slots:
      /**
        * @brief Called when m_request finished.
        *
        * @param result Result of m_request.
        * @return void
        **/
      void requestFinished(QVariant result);
};
    
  }
}

#endif // GET_H
