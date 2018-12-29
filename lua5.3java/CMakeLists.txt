
cmake_minimum_required(VERSION 3.4.1)

include_directories(${CMAKE_SOURCE_DIR}/src/main/jni/lua)
#添加lua静态库
add_library(
             lua

             STATIC

             ${CMAKE_SOURCE_DIR}/src/main/jni/lua/lapi.c
             ${CMAKE_SOURCE_DIR}/src/main/jni/lua/lauxlib.c
             ${CMAKE_SOURCE_DIR}/src/main/jni/lua/lbaselib.c
             ${CMAKE_SOURCE_DIR}/src/main/jni/lua/lbitlib.c
             ${CMAKE_SOURCE_DIR}/src/main/jni/lua/lcode.c
             ${CMAKE_SOURCE_DIR}/src/main/jni/lua/lcorolib.c
             ${CMAKE_SOURCE_DIR}/src/main/jni/lua/lctype.c
             ${CMAKE_SOURCE_DIR}/src/main/jni/lua/ldblib.c
             ${CMAKE_SOURCE_DIR}/src/main/jni/lua/ldebug.c
             ${CMAKE_SOURCE_DIR}/src/main/jni/lua/ldo.c
             ${CMAKE_SOURCE_DIR}/src/main/jni/lua/ldump.c
             ${CMAKE_SOURCE_DIR}/src/main/jni/lua/lfunc.c
             ${CMAKE_SOURCE_DIR}/src/main/jni/lua/lgc.c
             ${CMAKE_SOURCE_DIR}/src/main/jni/lua/linit.c
             ${CMAKE_SOURCE_DIR}/src/main/jni/lua/liolib.c
             ${CMAKE_SOURCE_DIR}/src/main/jni/lua/llex.c
             ${CMAKE_SOURCE_DIR}/src/main/jni/lua/lmathlib.c
             ${CMAKE_SOURCE_DIR}/src/main/jni/lua/lmem.c
             ${CMAKE_SOURCE_DIR}/src/main/jni/lua/loadlib.c
             ${CMAKE_SOURCE_DIR}/src/main/jni/lua/lobject.c
             ${CMAKE_SOURCE_DIR}/src/main/jni/lua/lopcodes.c
             ${CMAKE_SOURCE_DIR}/src/main/jni/lua/loslib.c
             ${CMAKE_SOURCE_DIR}/src/main/jni/lua/lparser.c
             ${CMAKE_SOURCE_DIR}/src/main/jni/lua/lstate.c
             ${CMAKE_SOURCE_DIR}/src/main/jni/lua/lstring.c
             ${CMAKE_SOURCE_DIR}/src/main/jni/lua/lstrlib.c
             ${CMAKE_SOURCE_DIR}/src/main/jni/lua/ltable.c
             ${CMAKE_SOURCE_DIR}/src/main/jni/lua/ltablib.c
             ${CMAKE_SOURCE_DIR}/src/main/jni/lua/ltm.c
             ${CMAKE_SOURCE_DIR}/src/main/jni/lua/lundump.c
             ${CMAKE_SOURCE_DIR}/src/main/jni/lua/lutf8lib.c
             ${CMAKE_SOURCE_DIR}/src/main/jni/lua/lvm.c
             ${CMAKE_SOURCE_DIR}/src/main/jni/lua/lzio.c

             ${CMAKE_SOURCE_DIR}/src/main/jni/android/androidlib.c
             ${CMAKE_SOURCE_DIR}/src/main/jni/android/input_event.c
             ${CMAKE_SOURCE_DIR}/src/main/jni/android/shell_cmd.c
             ${CMAKE_SOURCE_DIR}/src/main/jni/android/event_test.c
             )
#添加luajava动态库
add_library(
             luajava
             SHARED
             ${CMAKE_SOURCE_DIR}/src/main/jni/luajava/luajava.c )

find_library( log-lib  log )
#链接luajava lua log库
target_link_libraries( luajava  lua  ${log-lib} )


#生成叉叉unzip动态库
#ADD_SUBDIRECTORY(${CMAKE_SOURCE_DIR}/src/main/jni/unzip/xxunzip)

#生成自己的unzip动态库
ADD_SUBDIRECTORY(${CMAKE_SOURCE_DIR}/src/main/jni/unzip/myunzip)

ADD_SUBDIRECTORY(${CMAKE_SOURCE_DIR}/src/main/jni/test)
