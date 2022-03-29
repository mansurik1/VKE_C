.PHONY: configure build

configure:
	ls -la
	cmake -DBUILD_TESTS=on -B build

build:
	ls -la
	cd build
	ls -la
	cmake --build .