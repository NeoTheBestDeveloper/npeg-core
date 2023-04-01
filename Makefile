dev:
	meson compile -j 8 -C debug_build

release:
	meson compile -j 8 -C release_build
	strip release_build/libnpeg-core.so

setup:
	meson setup --buildtype=debug debug_build 

release_setup:
	meson setup --buildtype=release release_build -Db_sanitize=none

test:
	meson test -v -C debug_build

clean:
	rm -rf debug_build release_build
