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

#include "vkauth.h"
#include "qpcookiejar.h"

#include <QUrl>
#include <QWebView>

namespace Vk
{
  
  struct VkAuth::Data
  {
    QWebView *loginView;
    bool logged;
    QString token, cookieFile;
  };

  VkAuth::VkAuth(QObject *parent) :
    QObject(parent)
  {
    d = new Data;
    d->loginView = new QWebView;
    d->logged = false;
    connect(d->loginView, SIGNAL(urlChanged(QUrl)), this, SLOT(authUrlChanged(QUrl)));
    connect(d->loginView, SIGNAL(loadFinished(bool)), this, SLOT(authLoadFinished(bool)));
  }
    
  VkAuth::VkAuth(const QString& cookieFile, QObject* parent): 
    QObject(parent)
  {
    d = new Data;
    d->loginView = new QWebView;
    d->logged = false;
    d->cookieFile = cookieFile;
    connect(d->loginView, SIGNAL(urlChanged(QUrl)), this, SLOT(authUrlChanged(QUrl)));
    connect(d->loginView, SIGNAL(loadFinished(bool)), this, SLOT(authLoadFinished(bool)));
  }
  
  VkAuth::~VkAuth()
  {
    if( d->loginView )
      delete d->loginView;
    delete d;
  }



  QWebView *VkAuth::auth(QString appId, QString scope, QString display)
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
    if( !d->cookieFile.isEmpty() )
      d->loginView->page()->networkAccessManager()->setCookieJar( new QPCookieJar(d->cookieFile) );
    d->loginView->load(QUrl::fromUserInput(url));
    return d->loginView;
  }

  bool VkAuth::isLogged() const
  {
    return d->logged;
  }

  QString VkAuth::getToken() const
  {
    return d->token;
  }


  void VkAuth::authUrlChanged(const QUrl &url)
  {
    if( url.host() == "api.vk.com" && url.path() == "/blank.html" )
    {
      //TODO: handle errors
      const QUrl fixedUrl = QUrl::fromUserInput(url.toString().replace('#', '?'));
      const QString accessToken = fixedUrl.queryItemValue("access_token");
      const QString tokenExpiresIn = fixedUrl.queryItemValue("expires_in");
      if( !accessToken.isEmpty() )
      {
        d->logged = true;
        d->token = accessToken;
        emit authAccepted(accessToken);
      }
      d->loginView->deleteLater();
      d->loginView = 0;
    }
  }

  void VkAuth::authLoadFinished(bool ok)
  {
    //TODO: doesn't work sometimes
    if( !ok )
    {
      emit authCanceled();
      d->loginView->hide();
    }
  }
}
