PROJ_DIR 	:= $(CURDIR)
BUILD_DIR := ${PROJ_DIR}/build
SRC_DIR 	:= ${PROJ_DIR}/src
DEPS_DIR 	:= ${PROJ_DIR}/deps
RM 				:= rm -fr

.DEFAULT_GOAL := build
all: deps build
build: generate
	cmake --build "${BUILD_DIR}" --parallel
generate: clean
	cmake -B "${BUILD_DIR}" -S "${SRC_DIR}" -DCMAKE_MESSAGE_LOG_LEVEL=FATAL_ERROR
deps: clean
	${RM} "${DEPS_DIR}" && mkdir -p "${DEPS_DIR}" && ${PROJ_DIR}/entry.sh build-deps
clean:
	${RM} "${BUILD_DIR}"
run: build
	DYLD_LIBRARY_PATH=${BUILD_DIR}/lib ${BUILD_DIR}/bin/gtest
print-%:
	@echo $* = $($*)
.PHONY: all clean build deps run generate
