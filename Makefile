.PHONY: all clean format debug release duckdb_debug duckdb_release pull update

all: release

OSX_BUILD_UNIVERSAL_FLAG=
ifeq (${OSX_BUILD_UNIVERSAL}, 1)
	OSX_BUILD_UNIVERSAL_FLAG=-DOSX_BUILD_UNIVERSAL=1
endif

ifeq ($(GEN),ninja)
	GENERATOR=-G "Ninja"
	FORCE_COLOR=-DFORCE_COLORED_OUTPUT=1
endif

BUILD_FLAGS=-DEXTENSION_STATIC_BUILD=1 -DBUILD_TPCH_EXTENSION=1 -DBUILD_PARQUET_EXTENSION=1 ${OSX_BUILD_UNIVERSAL_FLAG}

ifeq (${BUILD_PYTHON}, 1)
	BUILD_FLAGS:=${EXTENSIONS} -DBUILD_PYTHON=1 -DBUILD_JSON_EXTENSION=1 -DBUILD_FTS_EXTENSION=1 -DBUILD_TPCH_EXTENSION=1 -DBUILD_VISUALIZER_EXTENSION=1 -DBUILD_TPCDS_EXTENSION=1
endif

ifeq (${BUILD_R}, 1)
	BUILD_FLAGS:=${EXTENSIONS} -DBUILD_R=1
endif

pull:
	git submodule init
	git submodule update --recursive --remote

clean:
	rm -rf build

# Bundled builds will produce binaries with the extension already linked into them
debug_bundled:
	mkdir -p  build/debug && \
	cmake $(GENERATOR) $(FORCE_COLOR) -DCMAKE_BUILD_TYPE=Debug ${BUILD_FLAGS} -S ./ -B build/debug   && \
	cmake --build build/debug

release_bundled:
	mkdir -p build/release && \
	cmake $(GENERATOR) $(FORCE_COLOR) -DCMAKE_BUILD_TYPE=RelWithDebInfo ${BUILD_FLAGS} -S ./ -B build/release   && \
	cmake --build build/release

test_release:
	./build/release/duckdb/test/unittest --test-dir . "[sql]"

test_debug:
	./build/debug/duckdb/test/unittest --test-dir . "[sql]"

# TODO make this clever
format:
	clang-format --sort-includes=0 -style=file -i src/boilerplate_extension.cpp
	cmake-format -i CMakeLists.txt
	cmake-format -i src/CMakeLists.txt

update:
	git submodule update --remote --merge