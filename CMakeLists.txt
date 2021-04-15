cmake_minimum_required(VERSION 3.2)

option(BUILD_SHARED_LIBS "Create shared libraries if ON" OFF)

project(pystring LANGUAGES CXX)

# pystring library ======

add_library(pystring
    pystring.cpp
    pystring.h
)
set_target_properties(pystring
    PROPERTIES
        PUBLIC_HEADER pystring.h
        SOVERSION 0.0)

set(EXPORT_NAME "${PROJECT_NAME}Targets")
set(NAMESPACE "${PROJECT_NAME}::")

# test ======

include(CTest)

if(BUILD_TESTING)
    add_executable(pystring_test
        test.cpp
        unittest.h
    )

    target_link_libraries(pystring_test pystring)

    add_test(NAME pystring_test COMMAND pystring_test)
endif()

# install and cmake configs ======

include(GNUInstallDirs)
install(TARGETS pystring
        EXPORT "${EXPORT_NAME}"
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pystring)

include(CMakePackageConfigHelpers)
configure_package_config_file(cmake/pystringConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/pystringConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/pystring)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/pystringConfig.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/pystring)

install(EXPORT "${EXPORT_NAME}"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/pystring
        NAMESPACE "${NAMESPACE}")
