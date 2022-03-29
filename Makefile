.PHONY: configure build test

configure:
	cmake -DBUILD_TESTS=on -B build

build:
	cmake --build ./build

test:
	ls -la
	ls -la build
	ls -la build/tests
	#./build/tests/flight_lib