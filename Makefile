ROOT_DIRECTORY = HW1
BUILD_DIRECTORY = build
TESTS_DIRECTORY = tests
LIB_DIRECTORY = flight_lib
MAIN_FILE_DIRECTORY = ${ ROOT_DIRECTORY }

.PHONY: format lint configure build test valgrind

format:
	chmod +x scripts/formatters.sh
	./scripts/formatters.sh

lint:
	chmod +x scripts/linters.sh
	./scripts/linters.sh

configure:
	cmake -DBUILD_TESTS=on -B ${BUILD_DIRECTORY}
	tree

build:
	make

test:
	# Testing
	chmod +x ${TESTS_DIRECTORY}/flight_test
	./${TESTS_DIRECTORY}/flight_test
	# Analyzing coverage
	lcov -t "${TESTS_DIRECTORY}/flight_test" -o coverage.info -c -d ${LIB_DIRECTORY}

valgrind:
	chmod +x /${ROOT_DIRECTORY}/scripts/valgrind.sh
	chmod +x flight_test
	./${ROOT_DIRECTORY}/scripts/valgrind.sh