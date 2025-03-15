project(
  'simple-game',
  'c',
  version: '0.1',
  default_options: ['warning_level=2', 'c_std=c23'],
)

# system dependencies
glfw_dep = dependency('glfw3')
cblas_dep = dependency('cblas')
cglm_dep = dependency('cglm')
open_gl_dep = dependency('gl')

cc = meson.get_compiler('c')
m_dep = cc.find_library('m', required: false)

deps = [glfw_dep, cblas_dep, cglm_dep, m_dep, open_gl_dep]

subdir('src')
incdir = include_directories('include')
exe = executable(
  'simple-game',
  sources: sources,
  include_directories: incdir,
  dependencies: deps,
  install: false,
)
