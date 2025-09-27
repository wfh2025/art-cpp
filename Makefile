PROJ_DIR 	:= $(CURDIR)
BUILD_DIR := ${PROJ_DIR}/build
SRC_DIR 	:= ${PROJ_DIR}/src
DEPS_DIR 	:= ${PROJ_DIR}/deps
RM 				:= rm -fr

.DEFAULT_GOAL := build

build: generate
	cmake --build "${BUILD_DIR}"
generate: clean
	cmake -B "${BUILD_DIR}" -S "${SRC_DIR}"
deps: clean
	${RM} "${DEPS_DIR}" && mkdir -p "${DEPS_DIR}" && ${PROJ_DIR}/entry.sh build-deps
clean:
	${RM} "${BUILD_DIR}"
run: build
	${BUILD_DIR}/bin/gtest-demo
print-%:
	@echo $* = $($*)
.PHONY: clean build deps
