cmake_minimum_required(VERSION 3.21)
project(crypto C)

set(CMAKE_C_STANDARD 99)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk4)
find_package(GTK REQUIRED gtk4)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

include_directories(${GTK4_INCLUDE_DIRS})
link_directories(${GTK4_LIBRARY_DIRS})

add_definitions(${GTK4_CFLAGS_OTHER})


file(GLOB sources *.c)
file(GLOB headers *.h)


add_executable(crypto ${sources} ${headers} entry.h interface.h base64.h)

target_link_libraries(crypto ${GTK4_LIBRARIES})