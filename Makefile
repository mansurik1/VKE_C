.PHONY: configure build

configure:
	ls -la
	cmake -DBUILD_TESTS=on -B build

build:
	cmake --build ./build