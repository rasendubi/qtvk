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

#include "vkcustomrequest.h"

#include <QtDebug>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QStringList>
#include <QUrl>

#include <qjson/parser.h>

namespace Vk
{
  
struct VkCustomRequest::Data
{
  QString method;
  QMap<QString,QString> params;
  
  QNetworkReply *reply;
  QNetworkAccessManager *manager;
  
  QVariant result;  
};

VkCustomRequest::VkCustomRequest(QString method, QMap< QString, QString > params, QObject* parent)
  : QObject(parent)
{
  d = new Data;
  d->method = method;
  d->params = params;
  d->reply = 0;
  d->manager = new QNetworkAccessManager(this);
}

VkCustomRequest::~VkCustomRequest()
{
  if( d->manager )
    delete d->manager;
  if( d->reply )
    delete d->reply;
  delete d;
}

void VkCustomRequest::exec()
{
  QUrl temp("https://api.vk.com/method/");
  temp.setPath(temp.path() + d->method);
  for( QMap<QString, QString>::iterator i = d->params.begin(); i != d->params.end(); i++ )
    temp.addQueryItem(d->params.key(*i), *i);
  
  d->reply = d->manager->get(QNetworkRequest(temp));
#ifndef QT_NO_DEBUG
  qDebug() << temp.toString();
#endif
  connect(d->reply, SIGNAL(finished()), this, SLOT(slotDone()));

}

void VkCustomRequest::slotDone()
{
  QJson::Parser parser;
  bool ok;
#ifndef QT_NO_DEBUG
  QString str = d->reply->readAll();
  qDebug() << "\n" << str;
  QByteArray arr(str.toStdString().c_str());
  d->result = parser.parse(arr, &ok);
#else
  d->result = parser.parse(d->reply, &ok);
#endif
  if( ok )
    emit result(d->result);
  else 
    qWarning() << "json parsing failed";
  d->reply->deleteLater();
  d->reply = 0;
}

QVariant VkCustomRequest::getResult() const
{
  return d->result;
}

}

