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

#ifndef QTVK_ACCESSMANAGER_H
#define QTVK_ACCESSMANAGER_H

#include "qtvkglobal.h"

#include <QObject>
#include <QString>

class QNetworkAccessManager;
class QUrl;
class QWebPage;
namespace QtVk
{
  class QTVK_EXPORT AccessManager : public QObject
  {
    Q_OBJECT
  public:
    /**
     * @brief Standard constructor.
     *
     * @param parent QObject parent
     **/
    explicit AccessManager(QObject* parent = 0);
    /**
     * @brief Destructor
     *
     **/
    virtual ~AccessManager();
    
    /**
     * @brief Authenticate in vk.com
     *
     * @param appId Your application id.
     * @param scope What permissions do you want to obtain. Comma separated string of values. Defaults to "". <br>
     *       - Available values <br>
     *         + notify, friends, photos, audio, video, docs, notes, pages, offers, questions, wall, 
     *           groups, messages, notifications, stats, ads, offline, nohttps
     * @param display Type of login screen. Defaults to "page".
     *       - Available values
     *         + page, popup, touch, wap
     * @return QWebPage* which you must display to give chance to user to log in.
     * @see authAccepted
     * @see authCanceled
     **/
    QWebPage *authentication(QString appId, QString scope = "", QString display = "page");
    
    void setNetworkAccessManager(QNetworkAccessManager *manager);
    QNetworkAccessManager *networkAccessManager() const;
    
    QString token() const;
    
  public slots:
    void setToken(const QString& token);
    
  signals:
    /**
     * @brief Emited when user accepted authorization
     * @param token Vk.com token
     * @see authentication
     * @see authCanceled
     */
    void authAccepted(const QString& token);
    
    /** 
     * @brief Emited when user cancel authorization 
     * @see authentication
     * @see authAccepted
     */
    void authCanceled();
    
  private slots:
    void authUrlChanged(const QUrl &url);
    void authLoadFinished(bool ok);
    
  private:
    struct AccessManagerPrivate;
    AccessManagerPrivate *d;
  };
}
#endif // QTVK_ACCESSMANAGER_H
