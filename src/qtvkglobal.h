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

#ifndef QTVKGLOBAL_H
#define QTVKGLOBAL_H

#include <QtCore/qglobal.h>

#define QTVK_VERSION_STR "0.2.0"
// QTVK_VERSION is (major << 16) + (minor << 8) + patch. Similar to Qt.
#define QTVK_VERSION 0x000200
// Use: #if (QTVK_VERSION >= QTVK_VERSION_CHECK(2, 0, 0)). Similar to Qt.
#define QTVK_VERSION_CHECK(major, minor, patch) ((major<<16)|(minor<<8)|(patch))

#if defined(QTVK_LIBRARY_BUILD)
#  define QTVK_EXPORT Q_DECL_EXPORT
#else
#  define QTVK_EXPORT Q_DECL_IMPORT
#endif

#endif // QTVKGLOBAL_H