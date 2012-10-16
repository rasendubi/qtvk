/*
 * QtVk. Qt interface for vk.com API
 * Copyright (C) 2012  Alexey Shmalko <dubi.rasen@gmail.com>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef GETCOUNT_H
#define GETCOUNT_H

#include <QObject>
#include <QString>
#include <QVariant>

namespace Vk
{
namespace Audio
{

/**
 * @brief Request returns count of audio of specified owner.
 * audio.getCount API
 */
class GetCount : public QObject
{
  Q_OBJECT
public:
  
  /**
   * @brief Standart constructor.
   * @param token Auth token
   * @param oid Owner id. <br>
   * If audio belongs to group, then oid = -id
   */
  explicit GetCount(const QString& token = "", int oid = 0, QObject* parent = 0);
  explicit GetCount(QObject* parent);
  virtual ~GetCount();
  
  /**
   * @brief Token setter.
   * @param token auth token
   */
  void setToken(const QString &token);
  /**
   * @brief Oid setter.
   * @param oid owner id
   */
  void setOid(int oid);
  
public slots:
  /**
   * @brief Execute request.
   */
  void exec();

signals:
  /**
   * @brief This signal is emmited when request finished.
   * @param result Count
   */
  void finished(int result);

private:
  struct Data;
  Data *d;

private slots:
  void requestFinished(QVariant result);
};

}
}

#endif // GETCOUNT_H
