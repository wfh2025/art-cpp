#!/usr/bin/env bash
export PROJ_ROOT=$(cd "$(dirname -- "$0")" && pwd -P)
export PROJ_BUILD=${PROJ_ROOT}/build
export PROJ_DEPS=${PROJ_ROOT}/deps
export PROJ_SRC=${PROJ_ROOT}/src
export PROJ_CMAKE=$(which cmake)
export PROJ_CC=$(which cc)
export PROJ_CXX=$(which c++)

function build-deps() {
    build-fmt
    build-zlib
    build-gflags
    build-pugixml
    build-leveldb
    build-civetweb
    build-googletest
    build-nlohmann-json
    build-abseil-cpp
}

function build-folly() {
    local build_dir="${PROJ_BUILD}"
    local install_dir="${PROJ_DEPS}/folly"
    local src="${PROJ_SRC}/third-party/folly-2026.01.05.00"

    rm -fr "${build_dir}" "${install_dir}" && mkdir -p "${install_dir}"

    ${PROJ_CMAKE} -B "${build_dir}" \
          -S "${src}" \
          -DCMAKE_BUILD_TYPE=Release \
          -DCMAKE_CXX_COMPILER="${PROJ_CXX}" \
          -DCMAKE_C_COMPILER="${PROJ_CC}" \
          -DCMAKE_INSTALL_PREFIX="${install_dir}" \
          -DBUILD_BENCHMARKS=OFF \
          -DBUILD_TESTS=OFF \
          -DBUILD_BROKEN_TESTS=OFF \
          -DBUILD_HANGING_TESTS=OFF -DBUILD_SLOW_TESTS=OFF
    ${PROJ_CMAKE} --build "${PROJ_BUILD}" --parallel --target install

    rm -fr "${build_dir}"
}

function build-aws-sdk-cpp() {
    # caution: 下载流程
    # git clone https://github.com/aws/aws-sdk-cpp && \
    #     cd aws-sdk-cpp && \
    #     git checkout 1.11.715 && \
    #     git submodule update --init --recursive

    local build_dir="${PROJ_BUILD}"
    local install_dir="${PROJ_DEPS}/aws-sdk-cpp"
    local src="${PROJ_SRC}/third-party/aws-sdk-cpp"

    rm -fr "${build_dir}" "${install_dir}" && mkdir -p "${install_dir}"
    
    ${PROJ_CMAKE} -B "${build_dir}" \
          -S "${src}" \
          -DCMAKE_BUILD_TYPE=Debug \
          -DCMAKE_CXX_COMPILER="${PROJ_CXX}" \
          -DCMAKE_INSTALL_PREFIX="${install_dir}" \
          -DBUILD_SHARED_LIBS=OFF \
          -DENABLE_TESTING=OFF \
          -DAUTORUN_UNIT_TESTS=OFF
    ${PROJ_CMAKE} --build "${PROJ_BUILD}" --config=Debug --parallel 8
    ${PROJ_CMAKE} --install "${PROJ_BUILD}" --config=Debug
    rm -fr "${build_dir}"
}

function build-zlog() {
    local build_dir="${PROJ_BUILD}"
    local install_dir="${PROJ_DEPS}/zlog"
    local src="${PROJ_SRC}/third-party/zlog-1.2.18"

    rm -fr "${build_dir}" "${install_dir}" && mkdir -p "${install_dir}"

    ${PROJ_CMAKE} -B "${build_dir}" \
          -S "${src}" \
          -DCMAKE_BUILD_TYPE=Release \
          -DCMAKE_CXX_COMPILER="${PROJ_CXX}" \
          -DCMAKE_C_COMPILER="${PROJ_CC}" \
          -DCMAKE_INSTALL_PREFIX="${install_dir}" \
          -DCMAKE_POLICY_VERSION_MINIMUM=3.5
    ${PROJ_CMAKE} --build "${PROJ_BUILD}" --parallel --target install

    rm -fr "${build_dir}"
}

function build-spdlog() {
    local build_dir="${PROJ_BUILD}"
    local install_dir="${PROJ_DEPS}/spdlog"
    local src="${PROJ_SRC}/third-party/spdlog-1.15.3"

    rm -fr "${build_dir}" "${install_dir}" && mkdir -p "${install_dir}"

    ${PROJ_CMAKE} -B "${build_dir}" \
          -S "${src}" \
          -DCMAKE_BUILD_TYPE=Release \
          -DCMAKE_CXX_COMPILER="${PROJ_CXX}" \
          -DCMAKE_INSTALL_PREFIX="${install_dir}" -DSPDLOG_BUILD_SHARED=OFF
    ${PROJ_CMAKE} --build "${PROJ_BUILD}" --parallel --target install

    rm -fr "${build_dir}"
}

function build-eigen() {
    local build_dir="${PROJ_BUILD}"
    local install_dir="${PROJ_DEPS}/eigen"
    local src="${PROJ_SRC}/third-party/eigen-5.0.1"

    rm -fr "${build_dir}" "${install_dir}" && mkdir -p "${install_dir}"

    ${PROJ_CMAKE} -B "${build_dir}" \
          -S "${src}" \
          -DCMAKE_BUILD_TYPE=Release \
          -DCMAKE_C_COMPILER="${PROJ_CC}" \
          -DCMAKE_INSTALL_PREFIX="${install_dir}" \
          -DBUILD_TESTING=OFF -DEIGEN_BUILD_TESTING=OFF
    ${PROJ_CMAKE} --build "${PROJ_BUILD}" --parallel --target install

    rm -fr "${build_dir}"
}

function build-libevent() {
    # https://codeload.github.com/libevent/libevent/tar.gz/refs/tags/release-2.1.12-stable
    local build_dir="${PROJ_BUILD}"
    local install_dir="${PROJ_DEPS}/libevent"
    local src="${PROJ_SRC}/third-party/libevent-release-2.1.12-stable"

    rm -fr "${build_dir}" "${install_dir}" && mkdir -p "${install_dir}"

    ${PROJ_CMAKE} -B "${build_dir}" \
          -S "${src}" \
          -DCMAKE_BUILD_TYPE=Release \
          -DCMAKE_C_COMPILER="${PROJ_CC}" \
          -DCMAKE_INSTALL_PREFIX="${install_dir}" \
          -DCMAKE_POLICY_VERSION_MINIMUM=3.5 \
          -DBUILD_TESTING=OFF \
          -DEVENT__LIBRARY_TYPE=BOTH \
          -DEVENT__DISABLE_OPENSSL=ON \
          -DEVENT__DISABLE_TESTS=ON
    ${PROJ_CMAKE} --build "${PROJ_BUILD}" --parallel --target install

    rm -fr "${build_dir}"
}

function build-zlib() {
    # https://zlib.net/zlib-1.3.1.tar.gz
    local build_dir="${PROJ_BUILD}"
    local install_dir="${PROJ_DEPS}/zlib"
    local src="${PROJ_SRC}/third-party/zlib-1.3.1"

    rm -fr "${build_dir}" "${install_dir}" && mkdir -p "${install_dir}"

    ${PROJ_CMAKE} -B "${build_dir}" \
          -S "${src}" \
          -DCMAKE_BUILD_TYPE=Release \
          -DCMAKE_C_COMPILER="${PROJ_CC}" \
          -DCMAKE_INSTALL_PREFIX="${install_dir}"
    ${PROJ_CMAKE} --build "${PROJ_BUILD}" --parallel --target install

    rm -fr "${build_dir}"
}

function build-civetweb() {
    local build_dir="${PROJ_BUILD}"
    local install_dir="${PROJ_DEPS}/civetweb"
    local src="${PROJ_SRC}/third-party/civetweb-1.16"

    rm -fr "${build_dir}" "${install_dir}" && mkdir -p "${install_dir}"

    ${PROJ_CMAKE} -B "${build_dir}" \
          -S "${src}" \
          -DCMAKE_POLICY_VERSION_MINIMUM=3.5 \
          -DBUILD_TESTING=OFF \
          -DCIVETWEB_BUILD_TESTING=OFF \
          -DCIVETWEB_ALLOW_WARNINGS=OFF \
          -DCIVETWEB_ENABLE_SSL=OFF \
          -DCIVETWEB_ENABLE_SSL_DYNAMIC_LOADING=OFF \
          -DCIVETWEB_ENABLE_SERVER_STATS=ON \
          -DCIVETWEB_ENABLE_CXX=ON \
          -DCMAKE_BUILD_TYPE=Release \
          -DCMAKE_C_COMPILER="${PROJ_CC}" \
          -DCMAKE_CXX_COMPILER="${PROJ_CXX}" \
          -DCMAKE_INSTALL_PREFIX="${install_dir}" \
          -DBUILD_SHARED_LIBS=OFF \
          -DCIVETWEB_ENABLE_MEMORY_DEBUGGING=ON \
          -DCIVETWEB_ENABLE_WEBSOCKETS=ON \
          -DCIVETWEB_INSTALL_EXECUTABLE=ON
    ${PROJ_CMAKE} --build "${PROJ_BUILD}" --parallel --target install

    rm -fr "${build_dir}"
}

function build-leveldb() {
    local build_dir="${PROJ_BUILD}"
    local install_dir="${PROJ_DEPS}/leveldb"
    local src="${PROJ_SRC}/third-party/leveldb-1.23"

    rm -fr "${build_dir}" "${install_dir}" && mkdir -p "${install_dir}"

    ${PROJ_CMAKE} -B "${build_dir}" \
          -S "${src}" \
          -DCMAKE_BUILD_TYPE=Release \
          -DCMAKE_C_COMPILER="${PROJ_CC}" \
          -DCMAKE_CXX_COMPILER="${PROJ_CXX}" \
          -DCMAKE_INSTALL_PREFIX="${install_dir}" \
          -DBUILD_SHARED_LIBS=OFF \
          -DCMAKE_POLICY_VERSION_MINIMUM=3.10 \
          -DLEVELDB_BUILD_BENCHMARKS=OFF \
          -DLEVELDB_BUILD_TESTS=OFF
    ${PROJ_CMAKE} --build "${PROJ_BUILD}" --parallel --target install

    rm -fr "${build_dir}"
}

function build-nlohmann-json() {
    local build_dir="${PROJ_BUILD}"
    local install_dir="${PROJ_DEPS}/json"
    local src="${PROJ_SRC}/third-party/json-3.12.0"

    rm -fr "${build_dir}" "${install_dir}" && mkdir -p "${install_dir}"

    ${PROJ_CMAKE} -B "${build_dir}" \
          -S "${src}" \
          -DCMAKE_BUILD_TYPE=Release \
          -DCMAKE_CXX_COMPILER="${PROJ_CXX}" \
          -DJSON_BuildTests=OFF \
          -DBUILD_SHARED_LIBS=OFF \
          -DCMAKE_INSTALL_PREFIX="${install_dir}"
    ${PROJ_CMAKE} --build "${PROJ_BUILD}" --parallel --target install

    rm -fr "${build_dir}"
}

function build-googletest() {
    local build_dir="${PROJ_BUILD}"
    local install_dir="${PROJ_DEPS}/googletest"
    local src="${PROJ_SRC}/third-party/googletest-1.17.0"

    rm -fr "${build_dir}" "${install_dir}" && mkdir -p "${install_dir}"
    ${PROJ_CMAKE} -B "${build_dir}" \
          -S "${src}" \
          -DCMAKE_BUILD_TYPE=Release \
          -DCMAKE_C_COMPILER="${PROJ_CC}" \
          -DCMAKE_CXX_COMPILER="${PROJ_CXX}" \
          -DBUILD_SHARED_LIBS=OFF \
          -DCMAKE_INSTALL_PREFIX="${install_dir}"
    ${PROJ_CMAKE} --build "${build_dir}" --parallel --target install
    rm -fr "${build_dir}"
}

function build-abseil-cpp() {
    local build_dir="${PROJ_BUILD}"
    local install_dir="${PROJ_DEPS}/abseil-cpp"
    local src="${PROJ_SRC}/third-party/abseil-cpp-20250814.1"

    rm -fr "${build_dir}" "${install_dir}" && mkdir -p "${install_dir}"
    ${PROJ_CMAKE} -B "${build_dir}" \
          -S "${src}" \
          -DCMAKE_BUILD_TYPE=Release \
          -DCMAKE_CXX_COMPILER="${PROJ_CXX}" \
          -DCMAKE_CXX_STANDARD=17 \
          -DBUILD_SHARED_LIBS=OFF \
          -DCMAKE_INSTALL_PREFIX="${install_dir}"
    ${PROJ_CMAKE} --build "${build_dir}" --parallel --target install
    rm -fr "${build_dir}"
}

function build-linenoise-ng() {
    local build_dir="${PROJ_BUILD}"
    local install_dir="${PROJ_DEPS}/linenoise-ng"
    local src="${PROJ_SRC}/third-party/linenoise-ng-1.0.1"

    rm -fr "${build_dir}" "${install_dir}" && mkdir -p "${install_dir}"
    ${PROJ_CMAKE} -B "${build_dir}" \
          -S "${src}" \
          -DCMAKE_BUILD_TYPE=Release \
          -DCMAKE_C_COMPILER="${PROJ_CC}" \
          -DCMAKE_CXX_COMPILER="${PROJ_CXX}" \
          -DBUILD_SHARED_LIBS=OFF \
          -DCMAKE_POLICY_VERSION_MINIMUM=3.5 \
          -Wno-dev \
          -DCMAKE_INSTALL_PREFIX="${install_dir}"
    ${PROJ_CMAKE} --build "${build_dir}" --parallel --target install
    rm -fr "${build_dir}"
}

function build-dlib() {
    local build_dir="${PROJ_BUILD}"
    local install_dir="${PROJ_DEPS}/dlib"
    local src="${PROJ_SRC}/third-party/dlib-20.0"

    rm -fr "${build_dir}" "${install_dir}" && mkdir -p "${install_dir}"
    ${PROJ_CMAKE} -B "${build_dir}" \
          -S "${src}" \
          -DCMAKE_BUILD_TYPE=Release \
          -DCMAKE_C_COMPILER="${PROJ_CC}" \
          -DCMAKE_CXX_COMPILER="${PROJ_CXX}" \
          -Wno-dev -DBUILD_SHARED_LIBS=OFF \
          -DCMAKE_INSTALL_PREFIX="${install_dir}"
    ${PROJ_CMAKE} --build "${build_dir}" --parallel --target install
    rm -fr "${build_dir}"
}

function build-fmt() {
    local build_dir="${PROJ_BUILD}"
    local install_dir="${PROJ_DEPS}/fmt"
    local src="${PROJ_SRC}/third-party/fmt-12.0.0"

    rm -fr "${build_dir}" "${install_dir}" && mkdir -p "${install_dir}"
    ${PROJ_CMAKE} -B "${build_dir}" \
          -S "${src}" \
          -DCMAKE_BUILD_TYPE=Release \
          -DCMAKE_CXX_COMPILER="${PROJ_CXX}" \
          -DFMT_TEST=OFF -DBUILD_SHARED_LIBS=OFF \
          -DCMAKE_INSTALL_PREFIX="${install_dir}"
    ${PROJ_CMAKE} --build "${build_dir}" --parallel --target install
    rm -fr "${build_dir}"
}

function build-gflags() {
    local build_dir="${PROJ_BUILD}"
    local install_dir="${PROJ_DEPS}/gflags"
    local src="${PROJ_SRC}/third-party/gflags-2.2.2"

    rm -fr "${build_dir}" "${install_dir}" && mkdir -p "${install_dir}"
    ${PROJ_CMAKE} -B "${build_dir}" \
          -S "${src}" \
          -DCMAKE_BUILD_TYPE=Release \
          -DCMAKE_CXX_COMPILER="${PROJ_CXX}" \
          -DBUILD_SHARED_LIBS=OFF \
          -DCMAKE_POLICY_VERSION_MINIMUM=3.10 \
          -DCMAKE_MINIMUM_REQUIRED_VERSION=3.10 \
          -DCMAKE_INSTALL_PREFIX="${install_dir}"
    ${PROJ_CMAKE} --build "${build_dir}" --parallel --target install
    rm -fr "${build_dir}"
}

function build-pugixml() {
    local build_dir="${PROJ_BUILD}"
    local install_dir="${PROJ_DEPS}/pugixml"
    local src="${PROJ_SRC}/third-party/pugixml-1.15"

    rm -fr "${build_dir}" "${install_dir}" && mkdir -p "${install_dir}"
    ${PROJ_CMAKE} -B "${build_dir}" \
          -S "${src}" \
          -DCMAKE_BUILD_TYPE=Release \
          -DCMAKE_CXX_COMPILER="${PROJ_CXX}" \
          -DBUILD_SHARED_LIBS=OFF \
          -DCMAKE_POLICY_VERSION_MINIMUM=3.5 \
          -DCMAKE_INSTALL_PREFIX="${install_dir}"
    ${PROJ_CMAKE} --build "${build_dir}" --parallel --target install
    rm -fr "${build_dir}"
}

function build-poco() {
    local build_dir="${PROJ_BUILD}"
    local install_dir="${PROJ_DEPS}/poco"
    local src="${PROJ_SRC}/third-party/poco-poco-1.14.2-release"

    rm -fr "${build_dir}" "${install_dir}" && mkdir -p "${install_dir}"
    ${PROJ_CMAKE} -B "${build_dir}" \
          -S "${src}" \
          -DCMAKE_BUILD_TYPE=Release \
          -DCMAKE_C_COMPILER="${PROJ_CC}" \
          -DCMAKE_CXX_COMPILER="${PROJ_CXX}" \
          -DBUILD_SHARED_LIBS=OFF \
          -DCMAKE_INSTALL_PREFIX="${install_dir}"
    ${PROJ_CMAKE} --build "${build_dir}" --parallel --target install
    rm -fr "${build_dir}"
}

function build-opencv() {
    local build_dir="${PROJ_BUILD}"
    local install_dir="${PROJ_DEPS}/opencv"
    local src="${PROJ_SRC}/third-party/opencv-4.12.0"
    local src_contrib="${PROJ_SRC}/third-party/opencv_contrib-4.12.0/modules"

    rm -fr "${build_dir}" "${install_dir}" && mkdir -p "${install_dir}"
    ${PROJ_CMAKE} -B "${build_dir}" -S "${src}" \
        -DCMAKE_INSTALL_PREFIX="${install_dir}" \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_C_COMPILER="${PROJ_CC}" \
        -DCMAKE_CXX_COMPILER="${PROJ_CXX}" \
        -Wno-dev \
        -DWITH_FFMPEG=OFF \
        -DBUILD_opencv_python_bindings_generator=OFF \
        -DBUILD_opencv_python_tests=OFF \
        -DBUILD_JAVA=OFF \
        -DBUILD_opencv_java_bindings_generator=OFF \
        -DBUILD_PERF_TESTS=OFF \
        -DBUILD_TESTS=OFF \
        -DOPENCV_TEST_DNN_TFLITE=OFF \
        -DOPENCV_TEST_DNN_CANN=OFF \
        -DOPENCV_TEST_DNN_OPENVINO=OFF \
        -DOPENCV_TEST_DNN_TIMVX=OFF \
        -DINSTALL_TESTS=OFF \
        -DBUILD_opencv_js=OFF \
        -DBUILD_opencv_js_bindings_generator=OFF \
        -DOPENCV_OSX_USE_ACCELERATE_NEW_LAPACK=ON \
        -DCMAKE_CXX_FLAGS="-Wno-deprecated-declarations -Wno-unused-result" \
        -DOPENCV_EXTRA_MODULES_PATH="${src_contrib}"
    ${PROJ_CMAKE} --build "${build_dir}" --parallel --target install
    rm -fr "${build_dir}"
}

function rm-rubbish() {
    find . -name ".DS_Store" -type f -delete
}

function main() {
    local funcName="$1"
    shift
    "$funcName" "$@"
}
main "$@"
