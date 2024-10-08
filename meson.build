project('mygitprompt', 'c',
        version: '0.0.1')


# Run 'git describe' to get the version information
git_describe = run_command('git', 'describe', '--tags', '--always').stdout().strip()

# If git describe fails (e.g. not in a git repo), provide a fallback version
if git_describe == ''
  git_describe = 'v0.0.0'
endif

# Pass the version to the C program using a compiler definition
add_project_arguments(['-DVERSION="' + git_describe + '"'], language: 'c')

# Define the source files
sources = ['mygitprompt.c', 'gitstatus.c']


# Define the include directories
inc = include_directories('.')

# Define the main executable
executable('mygitprompt', sources, include_directories: inc, install: true)

e = executable('mytest', sources: ['test.c', 'gitstatus.c'])
test('mygitprompt test', e)
