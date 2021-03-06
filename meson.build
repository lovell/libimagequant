project(
  'imagequant',
  'c',
  version : '2.4.1',
  license : 'BSD-2-Clause',
  meson_version : '>=0.48',
  default_options : [
    'c_std=c99',
  ],
)

compiler = meson.get_compiler('c')

if compiler.get_id() == 'gcc' or compiler.get_id() == 'clang'
  add_project_arguments(
    '-Wno-misleading-indentation',
    '-Wno-attributes',
    '-Wno-unknown-pragmas',
    language : 'c',
  )
endif

if host_machine.cpu_family() == 'x86_64'
  add_project_arguments(
    '-DUSE_SSE=1',
    language : 'c',
  )
endif

m = compiler.find_library(
  'm',
  required: false,
)

lib = library(
  'imagequant',
  'blur.c',
  'libimagequant.c',
  'mediancut.c',
  'mempool.c',
  'nearest.c',
  'pam.c',
  'viter.c',
  install : true,
  dependencies : [
    m,
  ],
)

install_headers('libimagequant.h')

import('pkgconfig').generate(
  lib,
  name : 'imagequant',
  description : 'Image quantisation',
)
