
BIN = mygitprompt
WORKDIR = $(shell pwd)/builddir

build:
	meson  compile -C $(WORKDIR)

init:
	meson setup $(WORKDIR) -Doptimization=3

clean:
	meson setup --wipe $(WORKDIR)

clean-all:
	rm -rf $(WORKDIR)

run:
	$(WORKDIR)/$(BIN)
