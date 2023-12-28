
build:
	meson  compile -C build

init:
	meson setup build/ -Doptimization=3

clean:
	meson setup --wipe build

clean-all:
	rm -rf build
