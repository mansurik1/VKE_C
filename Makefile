configure:
	ls -la
	cmake -DBUILD_TESTS=on -B build

build:
	cd build
	ls -la
	cmake --build .