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

#ifndef GETBYID_H
#define GETBYID_H

#include "../audiorequest.h"

#include <QObject>
#include <QStringList>
#include <QVariant>

namespace Vk
{
namespace Audio
{
  
/**
  * @brief Implementation of audio.getById API call.
  **/
class GetById : public AudioRequest
{
  Q_OBJECT
public:
  /**
   * @brief Default constructor.
   *
   * @param token Vk token. Defaults to "".
   * @param audios List of audio ids. Defaults to QStringList().
   * @param parent QObject parent. Defaults to 0.
   **/
  explicit GetById(QString token = "", QStringList audios = QStringList(), QObject *parent = 0);
  /**
   * @brief Constructor.
   *
   * @param token Vk token.
   * @param audios List of AudioFiles.
   * @param parent QObject parent. Defaults to 0.
   **/
  explicit GetById(QString token, QList<Vk::AudioFile> audios, QObject *parent = 0);
  /**
   * @brief Constructor.
   *
   * @param parent QObject parent.
   **/
  explicit GetById(QObject* parent);
  virtual ~GetById();
  
  /**
   * @brief Append audio id to requested list.
   *
   * @param str Audio id.
   * @return void
   **/
  void append(const QString& str);
  /**
   * @brief Append list of audio ids to requested list.
   *
   * @param lst List of Ids
   * @return void
   **/
  void append(const QStringList& lst);
  
  /**
   * @brief Append audio to list.
   *
   * @param audio AudioFile.
   * @return void
   **/
  void append(const Vk::AudioFile& audio);
  /**
   * @brief Append list of audios.
   *
   * @param audios List of AudioFiles
   * @return void
   **/
  void append(const QList<Vk::AudioFile> audios);
  /**
   * @brief Clear requested list.
   *
   * @return void
   **/
  void clear();
  /**
   * @brief Set Vk token.
   *
   * @param token Vk token.
   * @return void
   **/
  void setToken(QString token);
public slots:
  /**
   * @brief Execute request.
   *
   * @return void
   **/
  virtual void exec();
  
private:
  struct Data;
  Data *d;
};

} //namespace Audio
} //namespace Vk

#endif // GETBYID_H
