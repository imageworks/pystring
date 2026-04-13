cmake_minimum_required(VERSION 3.10)
project(pystring LANGUAGES CXX VERSION 1.2.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option (BUILD_SHARED_LIBS "Build shared libraries (set to OFF to build static libs)" ON)
option(PYSTRING_HEADER_ONLY "Build as header-only library" OFF)

# If the user hasn't configured cmake with an explicit
# -DCMAKE_INSTALL_PREFIX=..., then set it to safely install into ./dist, to
# help prevent the user from accidentally writing over /usr/local or whatever.
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT
      AND PROJECT_IS_TOP_LEVEL)
    set (CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/dist" CACHE PATH
         "Installation location" FORCE)
endif()
message (STATUS "Installation path will be ${CMAKE_INSTALL_PREFIX}")
include(GNUInstallDirs)

if(PYSTRING_HEADER_ONLY)
    message(STATUS "Building pystring as header-only library")
    add_library(pystring INTERFACE)

    target_compile_definitions(pystring INTERFACE PYSTRING_HEADER_ONLY)

    target_include_directories(pystring INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    )

    # Install both headers for header-only mode
    install(FILES pystring.h pystring_impl.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
    )
else()
    message(STATUS "Building pystring as compiled library")

    add_library(pystring
        pystring.cpp
        pystring.h
    )

    set_target_properties(pystring PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
    )

    install(TARGETS pystring
            LIBRARY DESTINATION lib
            RUNTIME DESTINATION bin
            ARCHIVE DESTINATION lib
    )

    install (FILES pystring.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
        COMPONENT developer
    )

endif()

# Test executable

add_executable (pystring_test test.cpp)
TARGET_LINK_LIBRARIES (pystring_test pystring)

enable_testing()
add_test(NAME PyStringTest COMMAND pystring_test)

