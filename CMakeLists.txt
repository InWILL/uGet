cmake_minimum_required(VERSION 3.10)

project(uGet)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DNDEBUG -mwindows")

add_compile_definitions(HAVE_GLIB)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB REQUIRED glib-2.0)
include_directories(
    ${GLIB_INCLUDE_DIRS}
)


add_subdirectory(uglib)
add_subdirectory(uget)
add_subdirectory(ui-gtk)