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

#include "qpcookiejar.h"

#include <QFile>
#include <QtNetwork/QNetworkCookie>

struct QPCookieJar::Data
{
  QFile saveFile;
};

QPCookieJar::QPCookieJar(QString path, QObject* parent): QNetworkCookieJar(parent)
{
  d = new Data;
  d->saveFile.setFileName(path);
  QList<QNetworkCookie> cooks;
  if (!d->saveFile.open(QIODevice::ReadOnly | QIODevice::Text))
      return;

  while (!d->saveFile.atEnd()) {
      QByteArray line = d->saveFile.readLine();
      cooks.append(QNetworkCookie::parseCookies(line));
  }
  setAllCookies(cooks);
  d->saveFile.close();
}

QPCookieJar::~QPCookieJar()
{
  QList<QNetworkCookie> cooks = allCookies();
  d->saveFile.open(QIODevice::WriteOnly);
  foreach( QNetworkCookie cook, cooks )
  {
    QByteArray arr = cook.toRawForm();
#ifndef QT_NO_DEBUG
    qDebug("\n");
    qDebug(arr);
#endif
    d->saveFile.write(arr);
    d->saveFile.write("\n");
  }
  d->saveFile.close();
}


