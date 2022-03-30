.PHONY: configure build test lint

configure:
	cmake -DBUILD_TESTS=on -B build

build:
	cmake --build ./build

test:
	# Testing
	chmod +x build/tests/flight_test
	./build/tests/flight_test
	# Analyzing coverage
	lcov -t "build/tests/flight_test" -o build/coverage.info -c -d build/flight_lib
	tree build

lint:
	./linters/linters.sh