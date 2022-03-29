configure:
	cmake -DBUILD_TESTS=on -B build2

build:
	cd build2 \
	cmake --build .