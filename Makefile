configure:
	cmake -DBUILD_TESTS=on -B build

build:
	cd build \
	cmake --build .