project(
    'pystring',
    'cpp',
    version: '1.2.0',
    license: 'BSD-3-Clause',
    license_files: 'LICENSE',
    meson_version: '>=1.3',
    default_options: ['cpp_std=c++17,c++11', 'warning_level=3'],
)

# Option to build as header-only library
header_only = get_option('header_only')

inc = include_directories('.')
hdrs = files('pystring.h')

if header_only
    # Header-only mode: create a header-only dependency
    message('Building pystring as header-only library')

    pystring_dep = declare_dependency(
        include_directories: inc,
        compile_args: ['-DPYSTRING_HEADER_ONLY'],
    )

    # Install headers for header-only mode
    install_headers(hdrs, files('pystring_impl.h'), subdir: 'pystring')

else
    # Compiled mode: build as normal library
    message('Building pystring as compiled library')

    srcs = files('pystring.cpp')

    pystring_lib = library(
        'pystring',
        srcs,
        implicit_include_directories: false,
        include_directories: inc,
        version: meson.project_version(),
        install: true,
    )

    pystring_dep = declare_dependency(
        link_with: pystring_lib,
        include_directories: inc,
    )

    # Install headers for compiled mode
    install_headers(hdrs, subdir: 'pystring')

    # Generate pkg-config file
    pkgconfig = import('pkgconfig')
    pkgconfig.generate(
        pystring_lib,
        description: 'C++ functions matching the interface and behavior of python string methods with std::string',
    )
endif

meson.override_dependency('pystring', pystring_dep)

# Build and run tests
test(
    'PyStringTest',
    executable(
        'pystring_test',
        'test.cpp',
        dependencies: pystring_dep,
        build_by_default: false,
    ),
)
