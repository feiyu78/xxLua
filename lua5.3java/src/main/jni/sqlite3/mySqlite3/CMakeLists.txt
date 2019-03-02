#添加c++11的支持
set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")


add_library(
             lsqlite3
             SHARED
             ${CMAKE_SOURCE_DIR}/src/main/jni/sqlite3/mySqlite3/sqlite3.c
             ${CMAKE_SOURCE_DIR}/src/main/jni/sqlite3/mySqlite3/lsqlite3.c
             )

target_link_libraries(lsqlite3  luajava  ${log-lib})

