
BIN = mygitprompt
WORKDIR = $(shell pwd)/builddir

build:
	meson  compile -C $(WORKDIR)

init:
	meson setup $(WORKDIR) -Doptimization=3 -Dwarning_level=3

clean:
	meson setup --wipe $(WORKDIR)

clean-all:
	rm -rf $(WORKDIR)

run:
	$(WORKDIR)/$(BIN)

build-test:
	gcc -o builddir/test.exe test.c gitstatus.c -I.

test: build-test
	MALLOC_PERTURB_=126 ./builddir/test.exe
