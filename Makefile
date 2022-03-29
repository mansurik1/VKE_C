.PHONY: configure build

configure:
	cmake -DBUILD_TESTS=on -B build

build:
	cmake --build ./build

test:
	ls -la
	#./build/tests/flight_lib