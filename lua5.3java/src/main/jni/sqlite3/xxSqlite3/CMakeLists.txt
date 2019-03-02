
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
             lsqlite3
             SHARED
             ${CMAKE_SOURCE_DIR}/src/main/jni/sqlite3/xxSqlite3/sqlite3.c
             ${CMAKE_SOURCE_DIR}/src/main/jni/sqlite3/xxSqlite3/lsqlite3.cxx
             )


target_link_libraries(lsqlite3  xmod_extension_stub  ${log-lib})