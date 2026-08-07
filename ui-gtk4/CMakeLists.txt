cmake_minimum_required(VERSION 3.10)
project(uget-gtk4)

# 设置 C++ 标准
set(CMAKE_C_STANDARD 99)

# 设置 include 目录
include_directories(
    ${CMAKE_SOURCE_DIR}/ui-gtk4
    ${CMAKE_SOURCE_DIR}/uget
    ${CMAKE_SOURCE_DIR}/uglib
)

# 查找依赖库
pkg_check_modules(CURL REQUIRED libcurl)
pkg_check_modules(LIBGCRYPT REQUIRED libgcrypt)
pkg_check_modules(LIBCRYPTO REQUIRED libcrypto)
pkg_check_modules(GTK REQUIRED gtk4)
pkg_check_modules(LIBNOTIFY REQUIRED libnotify)
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)

# 源文件
set(SOURCES
    main.c

    ../Windows/resources/uget.rc
)

# 生成可执行文件
add_executable(uget-gtk4 ${SOURCES})

# 链接静态库和依赖项
add_library(libuget STATIC IMPORTED)
set_target_properties(libuget PROPERTIES IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/uget/libuget.a)

add_library(libuglib STATIC IMPORTED)
set_target_properties(libuglib PROPERTIES IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/uglib/libuglib.a)

# 链接库
target_link_libraries(uget-gtk4
    libuget
    libuglib
    ${LFS_LDFLAGS}
    ${CURL_LIBRARIES}
    ${LIBGCRYPT_LIBRARIES}
    ${LIBCRYPTO_LIBRARIES}
    ${GTK_LIBRARIES}
    ${LIBNOTIFY_LIBRARIES}
    ${APP_INDICATOR_LIBRARIES}
    ${GSTREAMER_LIBRARIES}
    ${LIBPWMD_LIBRARIES}
)

target_link_libraries(uget-gtk4 Ws2_32)

# 添加 include 目录
target_include_directories(uget-gtk4 PRIVATE
    ${CURL_INCLUDE_DIRS}
    ${LIBGCRYPT_INCLUDE_DIRS}
    ${LIBCRYPTO_INCLUDE_DIRS}
    ${GTK_INCLUDE_DIRS}
    ${LIBNOTIFY_INCLUDE_DIRS}
    ${APP_INDICATOR_INCLUDE_DIRS}
    ${GSTREAMER_INCLUDE_DIRS}
    ${LIBPWMD_INCLUDE_DIRS}
)
