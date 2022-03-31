.PHONY: configure fbinfer scan-build build tests valgrind address thread lint format

configure:
	cmake -DBUILD_TESTS=on -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -B build

fbinfer:
	infer run --fail-on-issue --compilation-database compile_commands.json

scan-build:
	scan-build -v cmake --build .

build:
	tree
	make

tests:
	# Testing
	chmod +x tests/flight_test
	./tests/flight_test
	# Analyzing coverage
	lcov -t "tests/flight_test" -o coverage.info -c -d flight_lib

valgrind:
	chmod +x scripts/valgrind.sh
	chmod +x build/tests/flight_test
	./scripts/valgrind.sh

address:
	chmod +x scripts/sanitizer_address.sh
	./scripts/sanitizer_address.sh

thread:
	chmod +x scripts/sanitizer_thread.sh
	./scripts/sanitizer_thread.sh

lint:
	chmod +x scripts/linters.sh
	./scripts/linters.sh

format:
	chmod +x scripts/formatters.sh
	./scripts/formatters.sh