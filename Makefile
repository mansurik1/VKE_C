.PHONY: format lint configure build test valgrind

format:
	chmod +x scripts/formatters.sh
	tree
	./scripts/formatters.sh

lint:
	chmod +x scripts/linters.sh
	./scripts/linters.sh

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

valgrind:
	chmod +x scripts/valgrind.sh
	chmod +x build/tests/flight_test
	./scripts/valgrind.sh