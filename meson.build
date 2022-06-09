project(
  'cprintf',
  'c',
  version: '1.0.1',
  default_options: [
    'b_pch=false',
    'b_vscrt=md',
    'buildtype=release',
    'warning_level=2'
  ]
)

cc = meson.get_compiler('c').get_id()
build_args = ['-DCPRINTF_BUILDING']
src = ['cprintf.c']

if cc != 'msvc'
  build_args += '-fPIC'
endif

if cc == 'msvc' or cc == 'clang-cl'
  build_args += '-D_CRT_SECURE_NO_WARNINGS'
endif

static_library(
  meson.project_name() + '_s',
  src,
  c_args: build_args
)

if cc == 'msvc' or cc == 'clang-cl'
  build_args += '-DCPRINTF_DLL'
endif

shared_library(
  meson.project_name(),
  src,
  c_args: build_args
)