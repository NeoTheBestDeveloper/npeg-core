debug: 
	meson compile -j 8 -C debug_build
	meson compile -j 8 -C debug_win_build

release:
	meson compile -j 8 -C release_build 
	strip release_build/libnpeg-core.so
	meson compile -v -j 8 -C release_win_build 
	x86_64-w64-mingw32-strip release_win_build/libnpeg-core.dll

setup: 
	meson setup --cross-file=.x86_64-w64-mingw32.txt --buildtype=debug debug_win_build -Db_sanitize=none
	meson setup --buildtype=debug debug_build

release_setup: 
	meson setup --buildtype=release --cross-file=.x86_64-w64-mingw32.txt release_win_build -Db_sanitize=none
	meson setup --buildtype=release release_build -Db_sanitize=none

test: 
	meson test -v -C debug_build

test_win: 
	meson test --suite npeg-core -C debug_win_build

checks: 
	find . -iname "*.[ch]" | xargs clang-format -i 
	find . -iname "*.[ch]" | xargs clang-tidy --config-file .clang-tidy

clean: 
	rm -rf debug_build release_build .cache debug_win_build release_win_build
