cmake_minimum_required(VERSION 3.15)
project(saccubus C)

set(CMAKE_C_STANDARD 11)

#####
include(ExternalProject)
ExternalProject_Add(sdl
        PREFIX ${CMAKE_BINARY_DIR}
        URL ${CMAKE_SOURCE_DIR}/external/SDL-1.2.15.tar.gz
        PATCH_COMMAND patch --strip=1 < ${CMAKE_SOURCE_DIR}/external/libsdl-1.2.15-const-xdata32.patch
        CONFIGURE_COMMAND ${CMAKE_BINARY_DIR}/src/sdl/configure --disable-shared --enable-shared --with-pic --disable-video-x11 --prefix=${CMAKE_BINARY_DIR} CFLAGS=-fPIC
        BUILD_COMMAND make
        INSTALL_DIR ${CMAKE_BINARY_DIR}
        INSTALL_COMMAND make install
        )
ExternalProject_Add(freetype2
        PREFIX ${CMAKE_BINARY_DIR}
        URL ${CMAKE_SOURCE_DIR}/external/freetype-2.10.0.tar.gz
        CONFIGURE_COMMAND ${CMAKE_BINARY_DIR}/src/freetype2/configure --disable-shared --enable-shared --with-pic --prefix=${CMAKE_BINARY_DIR} CFLAGS=-fPIC
        BUILD_COMMAND make
        INSTALL_DIR ${CMAKE_BINARY_DIR}
        INSTALL_COMMAND make install
        )
ExternalProject_Add(sdl_ttf
        PREFIX ${CMAKE_BINARY_DIR}
        URL ${CMAKE_SOURCE_DIR}/external/SDL_ttf-2.0.11.tar.gz
        CONFIGURE_COMMAND ${CMAKE_BINARY_DIR}/src/sdl_ttf/configure --prefix=${CMAKE_BINARY_DIR}
        BUILD_COMMAND make
        INSTALL_DIR ${CMAKE_BINARY_DIR}
        INSTALL_COMMAND make install
        )
include_directories(${CMAKE_BINARY_DIR}/include)
include_directories(${CMAKE_BINARY_DIR}/include/SDL) # FIXME
link_directories(${CMAKE_BINARY_DIR}/lib)
add_dependencies(sdl_ttf sdl)
add_dependencies(sdl_ttf freetype2)

# FIXME
add_library(sdl_rotozoom STATIC ${CMAKE_CURRENT_SOURCE_DIR}/external/SDL_rotozoom-1.6/SDL_rotozoom.c)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/SDL_rotozoom-1.6)
add_dependencies(sdl_rotozoom sdl)

#####
include_directories(.)
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
target_link_libraries(saccubus ${CMAKE_BINARY_DIR}/lib/libSDL.a)
add_dependencies(saccubus sdl)
target_link_libraries(saccubus ${CMAKE_BINARY_DIR}/lib/libfreetype.a)
add_dependencies(saccubus freetype2)
target_link_libraries(saccubus ${CMAKE_BINARY_DIR}/lib/libSDL_ttf.a)
add_dependencies(saccubus sdl_ttf)
target_link_libraries(saccubus sdl_rotozoom)
add_dependencies(saccubus sdl_rotozoom)
