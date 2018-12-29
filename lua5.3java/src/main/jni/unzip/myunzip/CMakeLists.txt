#添加c++11的支持
set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")


add_library(
             unzip
             SHARED
             ${CMAKE_SOURCE_DIR}/src/main/jni/unzip/myunzip/lua_unzip.cpp
             ${CMAKE_SOURCE_DIR}/src/main/jni/unzip/myunzip/ioapi.c
             ${CMAKE_SOURCE_DIR}/src/main/jni/unzip/myunzip/unzip.c
             )

target_link_libraries(unzip luajava  ${log-lib}  -lz)