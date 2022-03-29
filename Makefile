.PHONY: configure build test

configure:
	cmake -DBUILD_TESTS=on -B build

build:
	cmake --build ./build

test:
	# Testing
	chmod +x build/tests/flight_test
	./build/tests/flight_test
	# Analyzing coverage
	lcov -t "tests/flight_test" -o coverage.info -c -d flight_lib
