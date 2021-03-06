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

#ifndef AUDIOFILE_H
#define AUDIOFILE_H

#include <QString>
#include <QUrl>

namespace Vk
{
  struct AudioFile
  {
    /**
     * @brief audio id
     */
    int aid;
    
    /**
     * @brief owner id
     */
    int oid;
    
    /**
     * @brief song artist
     */
    QString artist;
    
    /**
     * @brief song title
     */
    QString title;
    
    /**
     * @brief song duration (in seconds)
     */
    int duration;
    
    /**
     * @brief url for downloading
     */
    QUrl url;
    
    /**
     * @brief lyrics id.
     * Can be returned by Audio::GetLyrics
     */
    int lyricsId;
    
    /**
     * @brief album id;
     */
    int album;
  };
}

#endif //AUDIOFILE_H
