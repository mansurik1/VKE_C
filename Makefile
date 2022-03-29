.PHONY: configure build test

configure:
	cmake -DBUILD_TESTS=on -B build

build:
	cmake --build ./build

test:
	chmod +x build/tests/flight_test
	./build/tests/flight_test