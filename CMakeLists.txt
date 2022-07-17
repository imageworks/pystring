cmake_minimum_required(VERSION 3.2)
project(pystring CXX)

set(BUILD_SHARED_LIBS YES)

add_library(pystring
    pystring.cpp
    pystring.h
)

add_executable (pystring_test test.cpp)
TARGET_LINK_LIBRARIES (pystring_test pystring)

enable_testing()
add_test(NAME PyStringTest COMMAND pystring_test)

include(GNUInstallDirs)

install(TARGETS pystring
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

