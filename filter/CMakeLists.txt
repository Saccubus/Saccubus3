cmake_minimum_required(VERSION 3.15)
project(saccubus C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(src)
include_directories(src/chat)
include_directories(src/comment)
include_directories(src/common)
include_directories(src/unicode)

add_executable(filter
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
