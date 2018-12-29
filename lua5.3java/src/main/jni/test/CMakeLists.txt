#添加c++11的支持
set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")


add_library(
             Add
             SHARED
             ${CMAKE_SOURCE_DIR}/src/main/jni/test/library.c
             )

target_link_libraries(Add  luajava  ${log-lib}  dl)

