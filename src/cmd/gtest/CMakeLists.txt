set(TARGET_NAME "art-cmd-gtest")
set(EXEC_NAME "gtest")

add_executable("${TARGET_NAME}" "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
set_target_properties("${TARGET_NAME}" PROPERTIES CXX_STANDARD 20
                                                  CXX_STANDARD_REQUIRED ON
                                                  CXX_EXTENSIONS OFF
                                                  OUTPUT_NAME "${EXEC_NAME}"
)

target_include_directories("${TARGET_NAME}" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}"
                                                    "${CMAKE_SOURCE_DIR}"
                                                    "${CMAKE_CURRENT_SOURCE_DIR}/utils"
                                                    "${ART_CXX_DEPS_DIR}/abseil-cpp/include"
                                                    "${ART_CXX_DEPS_DIR}/fmt/include"
                                                    "${ART_CXX_DEPS_DIR}/gflags/include"
                                                    "${ART_CXX_DEPS_DIR}/googletest/include"
                                                    "${ART_CXX_DEPS_DIR}/json/include"
                                                    "${ART_CXX_DEPS_DIR}/leveldb/include"
                                                    "${ART_CXX_DEPS_DIR}/pugixml/include"
                                                    "${ART_CXX_DEPS_DIR}/poco/include"
                                                    "${ART_CXX_DEPS_DIR}/spdlog/include"
                                                    "${CMAKE_SOURCE_DIR}/third-party/cmdline"
)

target_sources("${TARGET_NAME}" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/gtest/archive.cpp"
                                        "${CMAKE_CURRENT_SOURCE_DIR}/utils/utils.cpp"
                                        "${CMAKE_CURRENT_SOURCE_DIR}/cxx/lambda_test.cpp"
                                        "${CMAKE_CURRENT_SOURCE_DIR}/cxx/class_test.cpp"
                                        "${CMAKE_CURRENT_SOURCE_DIR}/cxx/limits_test.cpp"
                                        "${CMAKE_CURRENT_SOURCE_DIR}/cxx/utility_test.cpp"
                                        "${CMAKE_CURRENT_SOURCE_DIR}/cxx/system_error_test.cpp"
                                        "${CMAKE_CURRENT_SOURCE_DIR}/cxx/string_test.cpp"
                                        "${CMAKE_CURRENT_SOURCE_DIR}/cxx/oop_test.cpp"
                                        "${CMAKE_CURRENT_SOURCE_DIR}/cxx/ref_test.cpp"
                                        "${CMAKE_CURRENT_SOURCE_DIR}/cxx/stl_test.cpp"
                                        "${CMAKE_CURRENT_SOURCE_DIR}/cxx/any_test.cpp"
                                        "${CMAKE_CURRENT_SOURCE_DIR}/cxx/s3_test.cpp"
                                        "${CMAKE_CURRENT_SOURCE_DIR}/cxx/thread_test.cpp"
                                        "${CMAKE_CURRENT_SOURCE_DIR}/cxx/chrono_test.cpp"
                                        "${CMAKE_CURRENT_SOURCE_DIR}/third-party/absl_test.cpp"
                                        "${CMAKE_CURRENT_SOURCE_DIR}/third-party/fmt_test.cpp"
                                        "${CMAKE_CURRENT_SOURCE_DIR}/third-party/leveldb_test.cpp"
                                        "${CMAKE_CURRENT_SOURCE_DIR}/third-party/xml_test.cpp"
                                        "${CMAKE_CURRENT_SOURCE_DIR}/third-party/cmdline_test.cpp"
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
                                               "${ART_CXX_DEPS_DIR}/googletest/lib/libgtest.a"
                                               "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/libart_base.a"
                                               "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/libart_s3.a"
                                               "${ART_CXX_DEPS_DIR}/googletest/lib/libgmock.a"
                                               "${ART_CXX_DEPS_DIR}/fmt/lib/libfmt.a"
                                               "${ART_CXX_DEPS_DIR}/abseil-cpp/lib/libabsl_strings.a"
                                               "${ART_CXX_DEPS_DIR}/abseil-cpp/lib/libabsl_raw_logging_internal.a"
                                               "${ART_CXX_DEPS_DIR}/gflags/lib/libgflags.a"
                                               "${ART_CXX_DEPS_DIR}/gflags/lib/libgflags_nothreads.a"
                                               "${ART_CXX_DEPS_DIR}/pugixml/lib/libpugixml.a"
                                               "${ART_CXX_DEPS_DIR}/leveldb/lib/libleveldb.a"
                                               "${ART_CXX_DEPS_DIR}/spdlog/lib/libspdlog.a"
)