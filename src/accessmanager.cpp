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

#include "accessmanager.h"

#include <QNetworkAccessManager>
#include <QWebFrame>
#include <QWebPage>

struct QtVk::AccessManager::AccessManagerPrivate
{
  QString token;
  QWebPage *loginPage;
  QNetworkAccessManager *networkManager;
};

QtVk::AccessManager::AccessManager(QObject* parent )
  : QObject()
  , d(new AccessManagerPrivate())
{
  d->token = QString();
  d->networkManager = 0;
  d->loginPage = 0;
}

QtVk::AccessManager::~AccessManager()
{
  delete d;
}

QWebPage* QtVk::AccessManager::authentication(QString appId, QString scope, QString display)
{
  Q_ASSERT(!appId.isEmpty());
  const QString url = QString("http://api.vk.com/oauth/authorize?"
                              "client_id=%1&"
                              "scope=%2&"
                              "redirect_uri=http://api.vk.com/blank.html&"
                              "display=%3&"
                              "response_type=token")
                      .arg(appId)
                      .arg(scope)
                      .arg(display);
                      
  d->loginPage = new QWebPage(this);
  d->loginPage->setNetworkAccessManager(networkAccessManager());
  
  connect(d->loginPage->currentFrame(), SIGNAL(urlChanged(QUrl)), this, SLOT(authUrlChanged(QUrl)));
  connect(d->loginPage->currentFrame(), SIGNAL(loadFinished(bool)), this, SLOT(authLoadFinished(bool)));
  
  d->loginPage->currentFrame()->load(QUrl::fromUserInput(url));
  
  return d->loginPage;
}

void QtVk::AccessManager::authLoadFinished(bool ok)
{
  if( !ok )
  {
    emit authCanceled();
  }
  
  if( d->loginPage && d->loginPage->parent() == this )
    d->loginPage->deleteLater();
  d->loginPage = 0;
}

void QtVk::AccessManager::authUrlChanged(const QUrl& url)
{
  if( url.host() == "api.vk.com" && url.path() == "/blank.html" )
  {
    // TODO handle errors
    const QUrl fixedUrl = QUrl::fromUserInput(url.toString().replace('#', '?'));
    const QString accessToken = fixedUrl.queryItemValue("access_token");
    const QString tokenExpiresIn = fixedUrl.queryItemValue("expires_in");
    
    if( !accessToken.isEmpty() )
    {
      d->token = accessToken;
      emit authAccepted(accessToken);
    }
    else
      emit authCanceled();
  }
  
  if( d->loginPage && d->loginPage->parent() == this )
    d->loginPage->deleteLater();
  d->loginPage = 0;
}

QNetworkAccessManager* QtVk::AccessManager::networkAccessManager() const
{
  if( !d->networkManager )
  {
    AccessManager *that = const_cast<AccessManager *>(this);
    that->d->networkManager = new QNetworkAccessManager(that);
  }
  return d->networkManager;
}

void QtVk::AccessManager::setNetworkAccessManager(QNetworkAccessManager* manager)
{
  if( d->networkManager == manager )
    return;
  
  if( d->networkManager && d->networkManager->parent() == this )
    delete d->networkManager;
  
  d->networkManager = manager;
}

QString QtVk::AccessManager::token() const
{
  return d->token;
}

void QtVk::AccessManager::setToken(const QString& token)
{
  d->token = token;
}
