.PHONY: configure build

configure:
	cmake -DBUILD_TESTS=on -B build

build:
	cmake --build ./build

test:
	ls -la
	ls -la ..
	ls -la ../..
	ls -la ../../_actions/actions/checkout
	#./build/tests/flight_lib