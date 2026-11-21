gnome = import('gnome')

# Include directories
ui_inc = include_directories(
  '.',
  '../uget',
  '../uglib',
)

# GLib resource compiler
glib_compile_resources = find_program(
  'glib-compile-resources',
  required: true,
)

resource_c = custom_target(
  'gtk4-resources',
  input: 'gresource.xml',
  output: 'resources.c',
  command: [
    glib_compile_resources,
    '--target=@OUTPUT@',
    '--sourcedir=@CURRENT_SOURCE_DIR@',
    '--generate-source',
    '@INPUT@',
  ],
)

# Application sources
ui_sources = files(
  'main.c',
  'window.c',
)

ui_sources += resource_c

# Executable
executable(
  'uget-gtk4',
  ui_sources,
  include_directories: ui_inc,
  dependencies: common_deps,
  link_with: [
    uget_lib,
    uglib_lib,
  ],
  install: true,
)
