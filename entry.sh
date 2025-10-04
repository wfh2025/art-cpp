#!/usr/bin/env bash
export PROJ_ROOT=$(cd "$(dirname -- "$0")" && pwd -P)
export PROJ_BUILD=${PROJ_ROOT}/build
export PROJ_DEPS=${PROJ_ROOT}/deps
export PROJ_SRC=${PROJ_ROOT}/src

function build-deps() {
    build-googletest && \
    build-abseil-cpp && \
    build-pugixml && \
    build-fmt && \
    build-nlohmann-json && \
    build-linenoise-ng && \
    build-dlib && \
    build-gflags
}

function build-nlohmann-json() {
    rm -fr "${PROJ_BUILD}"
    mkdir -p "${PROJ_DEPS}/json" 
    cmake -B "${PROJ_BUILD}" \
          -S "${PROJ_SRC}/3rdparty/json-3.12.0" \
          -DCMAKE_BUILD_TYPE=Release \
          -DCMAKE_INSTALL_PREFIX="${PROJ_DEPS}/json" && \
    cmake --build "${PROJ_BUILD}" --parallel --target install
    rm -fr "${PROJ_BUILD}"
}

function build-googletest() {
    rm -fr "${PROJ_BUILD}"
    mkdir -p "${PROJ_DEPS}/googletest" 
    cmake -B "${PROJ_BUILD}" \
          -S "${PROJ_SRC}/3rdparty/googletest-1.17.0" \
          -DCMAKE_BUILD_TYPE=Release \
          -DCMAKE_INSTALL_PREFIX="${PROJ_DEPS}/googletest" && \
    cmake --build "${PROJ_BUILD}" --parallel --target install
    rm -fr "${PROJ_BUILD}"
}

function build-abseil-cpp() {
    rm -fr "${PROJ_BUILD}"
    mkdir -p "${PROJ_DEPS}/abseil-cpp" 
    cmake -B "${PROJ_BUILD}" \
          -S "${PROJ_SRC}/3rdparty/abseil-cpp-20250814.1" \
          -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_STANDARD=17 \
          -DCMAKE_INSTALL_PREFIX="${PROJ_DEPS}/abseil-cpp" && \
    cmake --build "${PROJ_BUILD}" --parallel --target install
    rm -fr "${PROJ_BUILD}"
}

function build-linenoise-ng() {
    rm -fr "${PROJ_BUILD}"
    mkdir -p "${PROJ_DEPS}/linenoise-ng" 
    cmake -B "${PROJ_BUILD}" \
          -S "${PROJ_SRC}/3rdparty/linenoise-ng-1.0.1" \
          -DCMAKE_BUILD_TYPE=Release -DCMAKE_POLICY_VERSION_MINIMUM=3.5 -Wno-dev \
          -DCMAKE_INSTALL_PREFIX="${PROJ_DEPS}/linenoise-ng" && \
    cmake --build "${PROJ_BUILD}" --parallel --target install
    rm -fr "${PROJ_BUILD}"
}

function build-dlib() {
    rm -fr "${PROJ_BUILD}"
    mkdir -p "${PROJ_DEPS}/dlib" 
    cmake -B "${PROJ_BUILD}" \
          -S "${PROJ_SRC}/3rdparty/dlib-20.0" \
          -DCMAKE_BUILD_TYPE=Release -Wno-dev \
          -DCMAKE_INSTALL_PREFIX="${PROJ_DEPS}/dlib" && \
    cmake --build "${PROJ_BUILD}" --parallel --target install
    rm -fr "${PROJ_BUILD}"
}



function build-fmt() {
    rm -fr "${PROJ_BUILD}"
    mkdir -p "${PROJ_DEPS}/fmt" 
    cmake -B "${PROJ_BUILD}" \
          -S "${PROJ_SRC}/3rdparty/fmt-12.0.0" \
          -DCMAKE_BUILD_TYPE=Release \
          -DCMAKE_INSTALL_PREFIX="${PROJ_DEPS}/fmt" && \
    cmake --build "${PROJ_BUILD}" --parallel --target install
    rm -fr "${PROJ_BUILD}"
}

function build-gflags() {
    rm -fr "${PROJ_BUILD}"
    mkdir -p "${PROJ_DEPS}/gflags" 
    cmake -B "${PROJ_BUILD}" \
          -S "${PROJ_SRC}/3rdparty/gflags-2.2.2" \
          -DCMAKE_BUILD_TYPE=Release -DCMAKE_POLICY_VERSION_MINIMUM=3.5 \
          -DCMAKE_INSTALL_PREFIX="${PROJ_DEPS}/gflags" && \
    cmake --build "${PROJ_BUILD}" --parallel --target install
    rm -fr "${PROJ_BUILD}"
}

function build-pugixml() {
    rm -fr "${PROJ_BUILD}"
    mkdir -p "${PROJ_DEPS}/pugixml" 
    cmake -B "${PROJ_BUILD}" \
          -S "${PROJ_SRC}/3rdparty/pugixml-1.15" \
          -DCMAKE_BUILD_TYPE=Release \
          -DCMAKE_INSTALL_PREFIX="${PROJ_DEPS}/pugixml" && \
    cmake --build "${PROJ_BUILD}" --parallel --target install
    rm -fr "${PROJ_BUILD}"
}

function main() {
    local funcName="$1"
    shift
    "$funcName" "$@"
}
main "$@"
