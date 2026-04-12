set(TARGET_NAME "cmd-test-cxx")
set(EXEC_NAME "test-cxx")

find_package(OpenSSL REQUIRED)
find_package(absl CONFIG REQUIRED PATHS "${ART_CXX_DEPS_DIR}/abseil-cpp" NO_DEFAULT_PATH)
find_package(gflags CONFIG REQUIRED PATHS "${ART_CXX_DEPS_DIR}/gflags" NO_DEFAULT_PATH)
find_package(GTest CONFIG REQUIRED PATHS "${ART_CXX_DEPS_DIR}/googletest" NO_DEFAULT_PATH)
find_package(nlohmann_json CONFIG REQUIRED PATHS "${ART_CXX_DEPS_DIR}/json" NO_DEFAULT_PATH)
find_package(leveldb CONFIG REQUIRED PATHS "${ART_CXX_DEPS_DIR}/leveldb" NO_DEFAULT_PATH)
find_package(pugixml CONFIG REQUIRED PATHS "${ART_CXX_DEPS_DIR}/pugixml" NO_DEFAULT_PATH)
find_package(spdlog CONFIG REQUIRED PATHS "${ART_CXX_DEPS_DIR}/spdlog" NO_DEFAULT_PATH)

add_executable("${TARGET_NAME}" "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
set_target_properties("${TARGET_NAME}" PROPERTIES CXX_STANDARD 20
                                                  CXX_STANDARD_REQUIRED ON
                                                  CXX_EXTENSIONS OFF
                                                  OUTPUT_NAME "${EXEC_NAME}"
)

target_include_directories("${TARGET_NAME}" PRIVATE "${CMAKE_SOURCE_DIR}"
                                                    "${CMAKE_CURRENT_SOURCE_DIR}"
                                                    "${OPENSSL_INCLUDE_DIR}"
                                                    "${ART_CXX_DEPS_DIR}/tinyformat/include"
                                                    "${CMAKE_SOURCE_DIR}/third-party/cmdline"
)

target_sources("${TARGET_NAME}" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/gut/gtest_archive.cpp"
                                        "${CMAKE_CURRENT_SOURCE_DIR}/gut/gtest_def.cpp"
                                        "${CMAKE_CURRENT_SOURCE_DIR}/cxx/lambda_test.cpp"
                                        "${CMAKE_CURRENT_SOURCE_DIR}/cxx/class_test.cpp"
                                        "${CMAKE_CURRENT_SOURCE_DIR}/cxx/cpy_test.cpp"
                                        "${CMAKE_CURRENT_SOURCE_DIR}/cxx/oop_test.cpp"
                                        "${CMAKE_CURRENT_SOURCE_DIR}/cxx/ref_test.cpp"
                                        "${CMAKE_CURRENT_SOURCE_DIR}/cxx/stl_test.cpp"
                                        "${CMAKE_CURRENT_SOURCE_DIR}/cxx/any_test.cpp"
                                        "${CMAKE_CURRENT_SOURCE_DIR}/stl/algorithm_test.cpp"
                                        "${CMAKE_CURRENT_SOURCE_DIR}/stl/memory_test.cpp"
                                        "${CMAKE_CURRENT_SOURCE_DIR}/stl/limits_test.cpp"
                                        "${CMAKE_CURRENT_SOURCE_DIR}/stl/utility_test.cpp"
                                        "${CMAKE_CURRENT_SOURCE_DIR}/stl/system_error_test.cpp"
                                        "${CMAKE_CURRENT_SOURCE_DIR}/stl/string_test.cpp"
                                        "${CMAKE_CURRENT_SOURCE_DIR}/stl/functional_test.cpp"
                                        "${CMAKE_CURRENT_SOURCE_DIR}/stl/thread_test.cpp"
                                        "${CMAKE_CURRENT_SOURCE_DIR}/stl/chrono_test.cpp"
                                        "${CMAKE_CURRENT_SOURCE_DIR}/stl/ratio_test.cpp"
                                        "${CMAKE_CURRENT_SOURCE_DIR}/third-party/s3_test.cpp"
                                        "${CMAKE_CURRENT_SOURCE_DIR}/third-party/openssl_test.cpp"
)

target_compile_definitions("${TARGET_NAME}" PRIVATE
                            SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG
)

target_compile_options("${TARGET_NAME}" PRIVATE -pthread
                                                -ggdb
                                                -Wno-unused-value
                                                -Wno-unused-parameter
                                                -Wno-return-stack-address
                                                -Wno-tautological-undefined-compare
)

add_dependencies("${TARGET_NAME}" "art-base-static" "art-s3-static")
target_link_libraries("${TARGET_NAME}" PRIVATE -pthread
                                               "${OPENSSL_LIBRARIES}"
                                               GTest::gtest
                                               GTest::gmock
                                               "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/libart_base.a"
                                               "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/libart_s3.a"
                                               absl::strings
                                               absl::raw_logging_internal
                                               gflags_static
                                               gflags_nothreads_static
                                               pugixml::pugixml
                                               spdlog::spdlog
                                               leveldb::leveldb
                                               nlohmann_json::nlohmann_json
)
