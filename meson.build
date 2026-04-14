project(
    'pystring',
    'cpp',
    version: '1.2.0',
    license: 'BSD-3-Clause',
    license_files: 'LICENSE',
    meson_version: '>=1.3',
    default_options: ['cpp_std=c++17,c++11', 'warning_level=3'],
)

inc = include_directories('.')
hdrs = files('pystring.h')

# --- Compiled library target ---
pystring_lib = library(
    'pystring',
    files('pystring.cpp'),
    implicit_include_directories: false,
    include_directories: inc,
    version: meson.project_version(),
    install: true,
)

pystring_dep = declare_dependency(
    link_with: pystring_lib,
    include_directories: inc,
)

install_headers(hdrs, subdir: 'pystring')

pkgconfig = import('pkgconfig')
pkgconfig.generate(
    pystring_lib,
    description: 'C++ functions matching the interface and behavior of python string methods with std::string',
)

# --- Header-only target ---
pystring_header_only_dep = declare_dependency(
    include_directories: inc,
    compile_args: ['-DPYSTRING_HEADER_ONLY'],
)

install_headers(hdrs, files('pystring_impl.h'), subdir: 'pystring')

# --- Override default dependency ---
meson.override_dependency('pystring', pystring_dep)

# --- Tests ---
test(
    'PyStringTest',
    executable(
        'pystring_test',
        'test.cpp',
        dependencies: pystring_dep,
        build_by_default: false,
    ),
)

test(
    'PyStringTestHeaderOnly',
    executable(
        'pystring_test_header_only',
        'test.cpp',
        dependencies: pystring_header_only_dep,
        build_by_default: false,
    ),
)

# Compile-time check that PYSTRING_HEADER_ONLY propagates correctly
executable(
    'pystring_test_header_only_define',
    'test_header_only_define.cpp',
    dependencies: pystring_header_only_dep,
    build_by_default: true,
)