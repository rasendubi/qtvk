cmake_minimum_required(VERSION 2.8)

project(qtvk)

set(qtvk_MAJOR_VERSION 0)
set(qtvk_MINOR_VERSION 1)
set(qtvk_PATCH_VERSION 3)
set(qtvk_VERSION
  ${qtvk_MAJOR_VERSION}.${qtvk_MINOR_VERSION}.${qtvk_PATCH_VERSION})

set(qtvk_SOURCES
        src/friends/get.cpp
        src/qpcookiejar.cpp
        src/audio/search.cpp
        src/audio/getcount.cpp
        src/audio/getbyid.cpp 
        src/audio/audiotools.cpp
        src/audio/get.cpp
        src/audiorequest.cpp
        src/tools.cpp
        src/vkauth.cpp
        src/vkcustomrequest.cpp)
set(qtvk_HEADERS_main
        src/qpcookiejar.h
        src/qtvknamespace.h
        src/audiofile.h
        src/audiorequest.h
        src/user.h
        src/vkauth.h
        src/vkcustomrequest.h)
set(qtvk_HEADERS_audio
        src/audio/search.h
        src/audio/getcount.h
        src/audio/getbyid.h
        src/audio/get.h)
set(qtvk_HEADERS_friends
        src/friends/get.h)
set(qtvk_HEADERS
    ${qtvk_HEADERS_main}
    ${qtvk_HEADERS_audio}
    ${qtvk_HEADERS_friends})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(QT_USE_QTWEBKIT TRUE)
find_package(Qt4 COMPONENTS QtCore QtNetwork QtWebkit REQUIRED)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

find_package(QJSON REQUIRED)
include_directories(${QJSON_INCLUDE_DIR})

qt4_wrap_cpp(qtvk_MOC_SOURCES ${qtvk_HEADERS})

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
link_directories(${QJSON_LIBRARY_DIRS})

add_library(qtvk_shared SHARED ${qtvk_HEADERS} ${qtvk_SOURCES} ${qtvk_MOC_SOURCES})
set_target_properties(qtvk_shared
                      PROPERTIES OUTPUT_NAME qtvk)
target_link_libraries(qtvk_shared ${QT_LIBRARIES} ${QJSON_LIBRARIES})


set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR include CACHE PATH
  "Installation directory for header files")

if(WIN32 AND NOT CYGWIN)
  set(DEF_INSTALL_CMAKE_DIR Cmake)
else()
  set(DEF_INSTALL_CMAKE_DIR lib/cmake/qtvk)
endif()
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH
  "Installation directory for CMake files")
  
foreach(p LIB BIN INCLUDE CMAKE)
  set(var INSTALL_${p}_DIR)
  if(NOT IS_ABSOLUTE "${${var}}")
    set(${var}_REL "${${var}}")
    set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()
  
export(TARGETS qtvk_shared
  FILE "${PROJECT_BINARY_DIR}/qtvkLibraryDepends.cmake")
export(PACKAGE qtvk)

file(RELATIVE_PATH CONF_REL_INCLUDE_DIR 
  "${INSTALL_CMAKE_DIR}" "${INSTALL_INCLUDE_DIR}")
configure_file(QtvkConfig.cmake.in
  "${PROJECT_BINARY_DIR}/QtvkConfig.cmake" @ONLY)

install(TARGETS qtvk_shared
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
install(FILES
  "${PROJECT_BINARY_DIR}/QtvkConfig.cmake"
  DESTINATION "${INSTALL_CMAKE_DIR_REL}" COMPONENT dev)

if(BUILD_STATIC)
  add_library(qtvk_static STATIC ${qtvk_HEADERS} ${qtvk_SOURCES} ${qtvk_MOC_SOURCES})
  set_target_properties(qtvk_static
                        PROPERTIES OUTPUT_NAME qtvk)
  target_link_libraries(qtvk_static ${QT_LIBRARIES} ${QJSON_LIBRARIES})
  install(TARGETS qtvk_static
          LIBRARY DESTINATION lib
          ARCHIVE DESTINATION lib)
endif(BUILD_STATIC)

install(FILES ${qtvk_HEADERS}
        DESTINATION include/qtvk COMPONENT dev)
install(FILES ${qtvk_HEADERS_audio}
        DESTINATION include/qtvk/audio COMPONENT dev)
install(FILES ${qtvk_HEADERS_friends}
        DESTINATION include/qtvk/friends COMPONENT dev)
        
include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_NAME "libqtvk")
set(CPACK_PACKAGE_VENDOR "Alexey Shmalko")
set(CPACK_PACKAGE_VERSION "${qtvk_VERSION}")
set(CPACK_GENERATOR "DEB;TBZ2")

set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Alexey Shmalko")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libqjson0, libqt4-network, libqtcore4, libqtgui4")
set(DEBIAN_PACKAGE_BUILDS_DEPENDS "libqjson0-dev")

include(CPack)
