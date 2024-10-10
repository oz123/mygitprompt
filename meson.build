project('mygitprompt', 'c',
        version: run_command('git', 'describe', '--tags', '--always', '||', 'echo', 'v0.0.1').stdout().strip())

# Pass the version to the C program using a compiler definition
add_project_arguments(['-DVERSION="' + meson.project_version() + '"'], language: 'c')

# Define the source files
sources = ['mygitprompt.c', 'gitstatus.c']

# Define the include directories
inc = include_directories('.')

# Define the main executable
executable('mygitprompt', sources, include_directories: inc, install: true)

e = executable('mytest', sources: ['test.c', 'gitstatus.c'])
test('mygitprompt test', e)
