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

#ifndef QTVK_REQUEST_H
#define QTVK_REQUEST_H

#include "qtvkglobal.h"

#include <QObject>
#include <QMap>

namespace QtVk
{

  class QTVK_EXPORT Request : public QObject
  {

  public:
      explicit Request(QObject* parent = 0);
      virtual ~Request();
      
      virtual QString method() const = 0;
      virtual QMap<QString, QString> params() const = 0;
  };
  
}

#endif // QTVK_REQUEST_H