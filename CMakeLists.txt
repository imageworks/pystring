cmake_minimum_required(VERSION 3.10)
project(pystring LANGUAGES CXX VERSION 1.1.4)

option (BUILD_SHARED_LIBS "Build shared libraries (set to OFF to build static libs)" ON)

# If the user hasn't configured cmake with an explicit
# -DCMAKE_INSTALL_PREFIX=..., then set it to safely install into ./dist, to
# help prevent the user from accidentally writing over /usr/local or whatever.
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT
      AND PROJECT_IS_TOP_LEVEL)
    set (CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/dist" CACHE PATH
         "Installation location" FORCE)
endif()
message (STATUS "Installation path will be ${CMAKE_INSTALL_PREFIX}")

add_library(pystring
    pystring.cpp
    pystring.h
)
set_target_properties(pystring PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
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

