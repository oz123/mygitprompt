project('mygitprompt', 'c', version: '0.0.1')

# Define the source files
sources = ['mygitprompt.c', 'gitstatus.c']


# Define the include directories
inc = include_directories('.')

# Define the main executable
executable('mygitprompt', sources, include_directories: inc)

e = executable('mytest', sources: ['test.c', 'gitstatus.c'])
test('mygitprompt test', e)
