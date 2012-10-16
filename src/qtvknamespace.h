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

#ifndef QTVKNAMESPACE_
#define QTVKNAMESPACE_

/**
 * @brief QtVk namespace.
 **/
namespace Vk
{
  /**
   * @brief Namespace for audio requests.
   **/
  namespace Audio
  {
    /**
     * @brief Enum for sorting tools.
     **/
    enum Sort
    {
      /**
       * @brief Sort by date.
       **/
      byDate = 0,
      /**
       * @brief Sort by duration.
       **/
      byDuration = 1,
      /**
       * @brief Sort by popularity.
       **/
      byPupularity = 2
    };    
  }
    /**
    * @brief Sex of user.
    **/
  enum Sex
  {
    /**
      * @brief Sex isn't setted.
      **/
    NoSex = 0,
    /**
      * @brief Female sex.
      **/
    Female = 1,
    /**
      * @brief Male sex.
      **/
    Male = 2
  };
}

#endif //QTVKNAMESPACE_