###
#  general configuration of the makefile itself
###
SHELL := /bin/bash
.DEFAULT_GOAL := help

.PHONY: help
help:
	@mh -f $(MAKEFILE_LIST) $(target) || echo "Please install mh from https://github.com/oz123/mh/releases/latest"
ifndef target
	@(which mh > /dev/null 2>&1 && echo -e "\nUse \`make help target=foo\` to learn more about foo.")
endif
BIN = mygitprompt
WORKDIR = $(shell pwd)/builddir

build: ## build the program
	meson compile -v -C $(WORKDIR) mygitprompt

build-static: ## build a statically linked binary
	meson compile -C $(WORKDIR) mygitprompt-static-linux-amd64

install:  ## install the binary
	meson install -C $(WORKDIR) --tags runtime

install-static:  ## install the binary
	meson install -C $(WORKDIR) --tags static

init: ## init meson build dir
	meson setup $(WORKDIR) -Doptimization=3 -Dwarning_level=3

clean: ## clean meson workdir
	meson setup --wipe $(WORKDIR)

clean-all: ## completly wipe meson workdir
	rm -rf $(WORKDIR)

run:  ## run the compiled program
	$(WORKDIR)/$(BIN)

build-test:  ## build the test binary
	gcc -g -o builddir/test.exe src/test.c src/gitstatus.c -I.

test: build-test ## run the test binary
	MALLOC_PERTURB_=12 ./builddir/test.exe

valgrind-check:  ## analyze the program using valgrind
	valgrind --leak-check=full -s ./builddir/test.exe
