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

#ifndef VKAUTH_H
#define VKAUTH_H

#include <QObject>
#include <QString>

class QUrl;
class QWebView;
namespace Vk
{

  class VkAuth : public QObject
  {
    Q_OBJECT
  public:
    explicit VkAuth(QObject *parent = 0);
    explicit VkAuth(const QString& cookieFile, QObject *parent = 0);
    virtual ~VkAuth();
    
    /**
     * @brief Authorize in vk.com
     *
     * @param appId Your application id.
     * @param scope What permissions you want to obtain comma separated in one string. Defaults to "". <br>
     *       - Avaible values <br>
     *         + notify, friends, photos, audio, video, docs, notes, pages, offers, questions, wall, 
     *           groups, messages, notifications, stats, ads, offline, nohttps
     * @param display Type of login screen. Defaults to "page".
     *       - Avaible values
     *         + page, popup, touch, wap
     * @return QWebView* Which you must display to give chance fo user to log in.
     **/
    QWebView *auth(QString appId, QString scope = "", QString display = "page");
    
    /**
    * @return   If user logged in.
    */
    bool isLogged() const;
    
    /**
     * @brief If user logged in, returns token.
     *
     * @return QString token.
     **/
    QString getToken() const;
    
  signals:
    /**
    * @brief Emited when user accepted authorization
    * @param token    Vk.com token
    */
    void authAccepted(QString token);
    
    /** @brief Emited when user cancel authorization */
    void authCanceled();

  private slots:
    void authUrlChanged(const QUrl &url);
    void authLoadFinished(bool ok);
    
  private:
    struct Data;
    Data *d;
    
  };
  
}
#endif // VKAUTH_H
