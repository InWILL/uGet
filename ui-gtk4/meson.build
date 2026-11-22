gnome = import('gnome')

# Include directories
ui_inc = include_directories(
  '.',
  '../uget',
  '../uglib',
)

gtk_dep = dependency('gtk4')

resources = gnome.compile_resources(
  'gtk4-resources',
  'gresource.xml',
)

# Application sources
ui_sources = files(
  'main.c'
)

# Executable
executable(
  'uget-gtk4',
  [ui_sources, resources],
  include_directories: ui_inc,
  install: true,
  dependencies: gtk_dep,
)
