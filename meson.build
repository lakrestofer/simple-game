project('simple-game', 'c',
  version : '0.1',
  default_options : ['warning_level=3', 'c_std=c11'])

subdir('src')
incdir = include_directories('include')


exe = executable(
  'simple-game',
  sources: sources,
  include_directories : incdir,
  install : true)

test('basic', exe)
