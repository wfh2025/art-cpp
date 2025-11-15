PROJ_DIR            := $(abspath $(CURDIR))
SRC_DIR             := ${PROJ_DIR}/src
DEPS_DIR            := ${PROJ_DIR}/deps
BUILD_DIR           := ${PROJ_DIR}/build
PROJ_CC             := $(shell which cc)
PROJ_CXX            := $(shell which c++)
RM                  := rm -fr
CMAKE               := cmake
MKDIR               := mkdir -p
.DEFAULT_GOAL       := build
CMAKE_GENERATOR     := Unix Makefiles

all: deps build
build: generate
	${CMAKE} --build "${BUILD_DIR}" --parallel
generate: clean
	${CMAKE} -B "${BUILD_DIR}" -S "${SRC_DIR}" \
	-G "${CMAKE_GENERATOR}" -DCMAKE_C_COMPILER="${PROJ_CC}" -DCMAKE_CXX_COMPILER="${PROJ_CXX}" \
	-DCMAKE_MESSAGE_LOG_LEVEL=FATAL_ERROR 
deps: clean
	${RM} "${DEPS_DIR}" && mkdir -p "${DEPS_DIR}" && ${PROJ_DIR}/entry.sh build-deps
clean:
	${RM} "${BUILD_DIR}"
run: build
	DYLD_LIBRARY_PATH=${BUILD_DIR}/lib ${BUILD_DIR}/bin/gtest
print-%:
	@echo $* = $($*)
.PHONY: all clean build deps run generate
