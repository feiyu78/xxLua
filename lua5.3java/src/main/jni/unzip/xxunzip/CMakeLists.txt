#添加c++11的支持
set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
#添加xmod_extension_stub库头文件
include_directories(${CMAKE_SOURCE_DIR}/src/main/jni/staticLua/xxLua/include)

#引用叉叉的xmod_extension_stub静态库
add_library(xmod_extension_stub
             STATIC
             IMPORTED)
set_target_properties(xmod_extension_stub
                      PROPERTIES IMPORTED_LOCATION
                      ${CMAKE_SOURCE_DIR}/src/main/jni/staticLua/xxLua/${ANDROID_ABI}/libxmod_extension_stub.a)

add_library(
             unzip
             SHARED
             ${CMAKE_SOURCE_DIR}/src/main/jni/unzip/xxunzip/ioapi.c
             ${CMAKE_SOURCE_DIR}/src/main/jni/unzip/xxunzip/unzip.c
             ${CMAKE_SOURCE_DIR}/src/main/jni/unzip/xxunzip/lua_unzip.cpp
             )

#find_library( log-lib  log)
target_link_libraries( unzip  xmod_extension_stub  ${log-lib}  -lz)