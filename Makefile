.PHONY: configure build test

configure:
	cmake -DBUILD_TESTS=on -B build

build:
	cmake --build ./build

test:
	./build/tests/flight_test