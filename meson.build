project('mygitprompt', 'c',
        version: run_command('./scripts/get_version.sh', check: true).stdout().strip(),)

# Pass the version to the C program using a compiler definition
add_project_arguments(['-DVERSION="' + meson.project_version() +'"'] , language: 'c')

# Define the source files
sources = ['src/mygitprompt.c', 'src/gitstatus.c']

# Define the include directories
inc = include_directories('src')

# Define the main executable
bin = executable('mygitprompt',
                 sources,
                 include_directories: inc,
                 install:true, install_tag: 'runtime')

# Define the static executable
static_link_args = ['-static']
if build_machine.system() != 'darwin'  # macOS doesn't support fully static linking
    static_bin = executable('mygitprompt-static-linux-amd64',
                           sources,
                           include_directories: inc,
                           link_args: static_link_args,
			   install: true,
                           install_tag: 'static')
endif

# Define test executable
test_executable = executable('mygitprompt-test', sources: ['src/test.c', 'src/gitstatus.c'])
test('mygitprompt test', test_executable)

