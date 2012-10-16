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

#ifndef USER_H
#define USER_H
#include "qtvknamespace.h"
#include <QString>
#include <QUrl>

namespace Vk
{
  struct User
  {
    int uid;
    QString firstName;
    QString lastName;
    QString nickname;
    Vk::Sex sex;
    bool online;
    QString birthDate;
    int city;
    int country;
    QUrl photo;
    QUrl photoMedium;
    QUrl photoMediumRec;
    QUrl photoBig;
    QUrl photoRec;
    QString screenName;
    bool hasMobile;
    int rate;
  };
    
}

#endif //USER_H