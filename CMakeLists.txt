cmake_minimum_required(VERSION 3.10)
project(pystring LANGUAGES CXX VERSION 1.2.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

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
include(GNUInstallDirs)

# --- Compiled library target: pystring::pystring ---
add_library(pystring
    pystring.cpp
    pystring.h
)

set_target_properties(pystring PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

target_include_directories(pystring PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

install(TARGETS pystring
    EXPORT pystringTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)


# --- Header-only target: pystring::pystring_header_only ---
add_library(pystring_header_only INTERFACE)

target_compile_definitions(pystring_header_only INTERFACE PYSTRING_HEADER_ONLY)

target_include_directories(pystring_header_only INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

install(TARGETS pystring_header_only
    EXPORT pystringTargets
)

install(FILES pystring.h pystring_impl.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
)

# --- Export & package config ---
install(EXPORT pystringTargets
    FILE pystringTargets.cmake
    NAMESPACE pystring::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/pystring
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
    cmake/pystringConfig.cmake.in
    pystringConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/pystring
)

write_basic_package_version_file(
    pystringConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/pystringConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/pystringConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/pystring
)

# --- Tests ---
add_executable(pystring_test test.cpp)
target_link_libraries(pystring_test pystring)

add_executable(pystring_test_header_only test.cpp)
target_link_libraries(pystring_test_header_only pystring_header_only)

# Compile-time check that PYSTRING_HEADER_ONLY propagates correctly
add_executable(pystring_test_header_only_define test_header_only_define.cpp)
target_link_libraries(pystring_test_header_only_define pystring_header_only)

enable_testing()
add_test(NAME PyStringTest COMMAND pystring_test)
add_test(NAME PyStringTestHeaderOnly COMMAND pystring_test_header_only)
