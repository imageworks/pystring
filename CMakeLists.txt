cmake_minimum_required(VERSION 3.2)
project(pystring CXX)

option (BUILD_SHARED_LIBS "Build shared libraries (set to OFF to build static libs)" ON)

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
install (FILES pystring.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
    COMPONENT developer
)

