project('imagequant', 'c',
  version : '2.4.1',
  license : 'BSD-2-Clause',
)

if (host_machine.cpu_family() == 'x86_64')
  add_project_arguments(
    '-DUSE_SSE=1',
    language : 'c',
  )
endif

m = meson.get_compiler('c').find_library('m')

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
  dependencies : [m],
)

install_headers('libimagequant.h')

import('pkgconfig').generate(
  lib,
  name : 'imagequant',
  description : 'Image quantisation',
)
