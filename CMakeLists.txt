cmake_minimum_required(VERSION 2.8)

project(qtvk)

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

set(QT_USE_QTWEBKIT TRUE)
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

qt4_wrap_cpp(qtvk_MOC_SOURCES ${qtvk_HEADERS})

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
#link_directories(.)

add_library(qtvk_shared SHARED ${qtvk_HEADERS} ${qtvk_SOURCES} ${qtvk_MOC_SOURCES})
set_target_properties(qtvk_shared
                      PROPERTIES OUTPUT_NAME qtvk)
target_link_libraries(qtvk_shared ${QT_LIBRARIES} qjson)

install(TARGETS qtvk_shared
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

if(BUILD_STATIC)
  add_library(qtvk_static STATIC ${qtvk_HEADERS} ${qtvk_SOURCES} ${qtvk_MOC_SOURCES})
  set_target_properties(qtvk_static
                        PROPERTIES OUTPUT_NAME qtvk)
  target_link_libraries(qtvk_static ${QT_LIBRARIES} qjson)
  install(TARGETS qtvk_static
          LIBRARY DESTINATION lib
          ARCHIVE DESTINATION lib)
endif(BUILD_STATIC)

install(FILES ${qtvk_HEADERS}
        DESTINATION include/qtvk)
install(FILES ${qtvk_HEADERS_audio}
        DESTINATION include/qtvk/audio)
install(FILES ${qtvk_HEADERS_friends}
        DESTINATION include/qtvk/friends)
        
include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_NAME "libqtvk")
set(CPACK_PACKAGE_VENDOR "Alexey Shmalko")
set(CPACK_PACKAGE_VERSION "0.1.2")
set(CPACK_GENERATOR "DEB;TBZ2")

set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Alexey Shmalko")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libqjson0, libqt4-network, libqtcore4, libqtgui4")
set(DEBIAN_PACKAGE_BUILDS_DEPENDS "libqjson0-dev")

include(CPack)
