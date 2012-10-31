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

#include "customrequest.h"

struct QtVk::CustomRequest::CustomRequestPrivate
{
  QString method;
  QMap<QString, QString> params;
};

QtVk::CustomRequest::CustomRequest(QObject* parent)
  : Request(parent)
  , d(new CustomRequestPrivate)
{

}

QtVk::CustomRequest::~CustomRequest()
{
  delete d;
}

QString QtVk::CustomRequest::method() const
{
  return d->method;
}

QMap< QString, QString > QtVk::CustomRequest::params() const
{
  return d->params;
}

void QtVk::CustomRequest::setMethod(const QString& method)
{
  d->method = method;
}

void QtVk::CustomRequest::setParams(const QMap< QString, QString >& params)
{
  d->params = params;
}
