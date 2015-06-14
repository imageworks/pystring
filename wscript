#! /usr/bin/env python

""" wscript for pystring """

CXXFLAGS = [
    '-g',
    '-O3',
    '-Wall',
    '-Wextra',
    '-Werror',
    '-Wshadow',
    '-Wconversion',
    '-Wcast-qual',
    '-Wformat=2'
]

def options(opt):
    opt.load('compiler_cxx')

def configure(conf):
    conf.load('compiler_cxx')
    conf.env.append_unique('CXXFLAGS', CXXFLAGS)

def build(bld):
    bld.shlib(
        source="pystring.cpp",
        target='pystring',
    )

    bld.program(
        source="test.cpp",
        target="unittest",
        use="pystring"
    )

    public_headers = ['pystring.h']
    bld.install_files("${PREFIX}/include/pystring", public_headers)
