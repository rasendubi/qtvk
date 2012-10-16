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

#ifndef VKCUSTOMREQUEST_H
#define VKCUSTOMREQUEST_H

#include <QMap>
#include <QObject>
#include <QString>
#include <QVariant>

namespace Vk
{
  class VkCustomRequest : public QObject
  {
    Q_OBJECT
  public:
    explicit VkCustomRequest(QString method, QMap<QString,QString> params = QMap<QString,QString>(), QObject* parent = 0);
    virtual ~VkCustomRequest();
    
    QVariant getResult() const;

  public slots:
    void exec();
  signals:
    void result(QVariant res);
    
  private slots:
    void slotDone();
    
  private:
    struct Data;
    Data *d;
  };
}
#endif // VKCUSTOMREQUEST_H
