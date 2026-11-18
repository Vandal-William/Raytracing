.PHONY: build-release build-debug start debug test test-debug clean

build-release:
	cmake -S . -B build/release -DCMAKE_BUILD_TYPE=Release
	cmake --build build/release

build-debug:
	cmake -S . -B build/debug -DCMAKE_BUILD_TYPE=Debug
	cmake --build build/debug

start: build-release
	./build/release/raytracer

debug: build-debug
	./build/debug/raytracer

test: build-release
	ctest --test-dir build/release --output-on-failure

test-debug: build-debug
	ctest --test-dir build/debug --output-on-failure

clean:
	rm -rf build
