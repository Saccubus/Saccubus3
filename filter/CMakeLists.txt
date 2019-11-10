cmake_minimum_required(VERSION 3.13)
project(saccubus C)

set(CMAKE_C_STANDARD 11)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    set(BUILD_HOST "--host=x86_64-w64-mingw32")
else()
    set(BUILD_HOST "")
endif()

#####
include(ExternalProject)
ExternalProject_Add(sdl_pkg
        PREFIX ${CMAKE_BINARY_DIR}
        URL ${CMAKE_SOURCE_DIR}/external/SDL-1.2.15.tar.gz
        PATCH_COMMAND patch --strip=1 < ${CMAKE_SOURCE_DIR}/external/libsdl-1.2.15-const-xdata32.patch
        CONFIGURE_COMMAND ${CMAKE_BINARY_DIR}/src/sdl_pkg/configure ${BUILD_HOST} --disable-shared --enable-static --with-pic --disable-video-x11 --disable-joystick --disable-cdrom --disable-audio --disable-directx --disable-timers --prefix=${CMAKE_BINARY_DIR} CFLAGS=-fPIC
        BUILD_COMMAND make
        INSTALL_DIR ${CMAKE_BINARY_DIR}
        INSTALL_COMMAND make install
        )
ExternalProject_Add(freetype2_pkg
        PREFIX ${CMAKE_BINARY_DIR}
        URL ${CMAKE_SOURCE_DIR}/external/freetype-2.10.0.tar.gz
        CONFIGURE_COMMAND ${CMAKE_BINARY_DIR}/src/freetype2_pkg/configure ${BUILD_HOST} --disable-shared --enable-static --with-pic --prefix=${CMAKE_BINARY_DIR} CFLAGS=-fPIC
        BUILD_COMMAND make
        INSTALL_DIR ${CMAKE_BINARY_DIR}
        INSTALL_COMMAND make install
        )
ExternalProject_Add(sdl_ttf_pkg
        PREFIX ${CMAKE_BINARY_DIR}
        URL ${CMAKE_SOURCE_DIR}/external/SDL_ttf-2.0.11.tar.gz
        CONFIGURE_COMMAND ${CMAKE_BINARY_DIR}/src/sdl_ttf_pkg/configure ${BUILD_HOST} --disable-shared --enable-static --without-zlib --without-png --with-freetype-prefix=${CMAKE_BINARY_DIR} --with-sdl-prefix=${CMAKE_BINARY_DIR} --prefix=${CMAKE_BINARY_DIR} LDFLAGS=-L${CMAKE_BINARY_DIR}/lib LIBS=-lfreetype CPPFLAGS=-I${CMAKE_BINARY_DIR}/include/freetype2
        BUILD_COMMAND make
        INSTALL_DIR ${CMAKE_BINARY_DIR}
        INSTALL_COMMAND make install
        )
ExternalProject_Add(iconv_pkg
        PREFIX ${CMAKE_BINARY_DIR}
        URL ${CMAKE_SOURCE_DIR}/external/libiconv-1.16.tar.gz
        CONFIGURE_COMMAND ${CMAKE_BINARY_DIR}/src/iconv_pkg/configure ${BUILD_HOST} --disable-shared --enable-static --with-pic --prefix=${CMAKE_BINARY_DIR} CFLAGS=-fPIC
        BUILD_COMMAND make
        INSTALL_DIR ${CMAKE_BINARY_DIR}
        INSTALL_COMMAND make install
        )
ExternalProject_Add(zlib_pkg
        PREFIX ${CMAKE_BINARY_DIR}
        URL ${CMAKE_SOURCE_DIR}/external/zlib-1.2.11.tar.gz
        CONFIGURE_COMMAND CC=${CMAKE_C_COMPILER} CFLAGS=-fPIC ${CMAKE_BINARY_DIR}/src/zlib_pkg/configure --64 --static --prefix=${CMAKE_BINARY_DIR}
        BUILD_COMMAND make
        BUILD_IN_SOURCE TRUE
        INSTALL_DIR ${CMAKE_BINARY_DIR}
        INSTALL_COMMAND make install
        )
ExternalProject_Add(libpng_pkg
        PREFIX ${CMAKE_BINARY_DIR}
        URL ${CMAKE_SOURCE_DIR}/external/libpng-1.6.37.tar.gz
        CONFIGURE_COMMAND ${CMAKE_BINARY_DIR}/src/libpng_pkg/configure ${BUILD_HOST} --disable-shared --enable-static --with-pic --with-zlib-prefix=${CMAKE_BINARY_DIR} --prefix=${CMAKE_BINARY_DIR} "CFLAGS=-fPIC" "CPPFLAGS=-I${CMAKE_BINARY_DIR}/include" "LDFLAGS=-L${CMAKE_BINARY_DIR}/lib"
        BUILD_COMMAND make
        INSTALL_DIR ${CMAKE_BINARY_DIR}
        INSTALL_COMMAND make install
        )
include_directories(${CMAKE_BINARY_DIR}/include)
include_directories(${CMAKE_BINARY_DIR}/include/SDL) # FIXME
include_directories(${CMAKE_BINARY_DIR}/include/freetype2) # FIXME
link_directories(${CMAKE_BINARY_DIR}/lib)
add_dependencies(sdl_pkg iconv_pkg)
add_dependencies(sdl_ttf_pkg sdl_pkg)
add_dependencies(sdl_ttf_pkg freetype2_pkg)
add_dependencies(freetype2_pkg libpng_pkg)
add_dependencies(freetype2_pkg zlib_pkg)
add_dependencies(libpng_pkg zlib_pkg)

# FIXME
add_library(SDL_rotozoom STATIC ${CMAKE_CURRENT_SOURCE_DIR}/external/SDL_rotozoom-1.6/SDL_rotozoom.c)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/SDL_rotozoom-1.6)
add_dependencies(SDL_rotozoom sdl_pkg)

#####
include_directories(src)
include_directories(src/chat)
include_directories(src/comment)
include_directories(src/common)
include_directories(src/unicode)

add_library(saccubus SHARED
        src/chat/chat.c
        src/chat/chat.h
        src/chat/chat_pool.c
        src/chat/chat_pool.h
        src/chat/chat_slot.c
        src/chat/chat_slot.h
        src/chat/process_chat.c
        src/chat/process_chat.h
        src/comment/adjustComment.c
        src/comment/adjustComment.h
        src/comment/com_surface.c
        src/comment/com_surface.h
        src/comment/render_unicode.c
        src/comment/render_unicode.h
        src/comment/shadow.c
        src/comment/shadow.h
        src/comment/surf_util.c
        src/comment/surf_util.h
        src/common/framehook_ext.h
        src/common/framehook_ext_old.h
        src/unicode/unitable.h
        src/unicode/uniutil.c
        src/unicode/uniutil.h
        src/april_fool.c
        src/april_fool.h
        src/framehook.c
        src/framehook.h
        src/main.c
        src/main.h
        src/mydef.h
        src/nicodef.h
        src/process.c
        src/process.h
        src/struct_define.h
        src/util.c
        src/util.h
        src/wakuiro.c
        src/wakuiro.h
        saccubus_adapter.h)
set_target_properties(saccubus PROPERTIES OUTPUT_NAME "saccubus")
set_target_properties(saccubus PROPERTIES PREFIX "")
add_dependencies(saccubus SDL_rotozoom)
add_dependencies(saccubus sdl_pkg)
add_dependencies(saccubus freetype2_pkg)
add_dependencies(saccubus sdl_ttf_pkg)
add_dependencies(saccubus iconv_pkg)
target_link_libraries(saccubus SDL_rotozoom)
target_link_libraries(saccubus SDL_ttf)
target_link_libraries(saccubus freetype)
target_link_libraries(saccubus SDLmain)
target_link_libraries(saccubus SDL)
target_link_libraries(saccubus iconv)
target_link_libraries(saccubus charset)
target_link_libraries(saccubus png)
target_link_libraries(saccubus z)
