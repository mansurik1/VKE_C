.PHONY: format address thread lint configure build test valgrind

format:
	chmod +x scripts/formatters.sh
	./scripts/formatters.sh

lint:
	chmod +x scripts/linters.sh
	./scripts/linters.sh

address:
	chmod +x scripts/sanitizer_address.sh
	./scripts/sanitizer_address.sh
	rm -f a.out

thread:
	chmod +x scripts/sanitizer_thread.sh
	./scripts/sanitizer_thread.sh
	rm -f a.out

configure:
	cmake -DBUILD_TESTS=on -B build
	tree

build:
	make

test:
	# Testing
	chmod +x tests/flight_test
	./tests/flight_test
	# Analyzing coverage
	lcov -t "tests/flight_test" -o coverage.info -c -d flight_lib

valgrind:
	chmod +x scripts/valgrind.sh
	chmod +x build/tests/flight_test
	./scripts/valgrind.sh