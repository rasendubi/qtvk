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


#ifndef SEARCH_H
#define SEARCH_H

#include <QObject>
#include <QString>
#include "../audiorequest.h"

namespace Vk
{
namespace Audio
{
  
class Search : public AudioRequest
{
  Q_OBJECT
  
public:
  explicit Search(const QString& token, const QString& q, bool autoComplete = true, bool withLyrics = false, int count = 0, int offset = 0, int sort = 2, QObject* parent = 0);
  explicit Search(QObject* parent = 0);
  virtual ~Search();
  
  void setQuery(const QString& query);
  void setAutoComplete(bool autoComplete);
  void setWithLyrics(bool withLyrics);
  void setSort(int sort);
  void setCount(int count);
  void setOffset(int offset);
  void setToken(const QString& token);

public slots:
  void exec();
      
private:
  struct Data;
  Data *d;
  
};

}
}

#endif // SEARCH_H
