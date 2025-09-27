set(TARGET_NAME "art-cmd-gtest-brew")
set(EXEC_NAME "gtest-brew")

add_executable("${TARGET_NAME}" "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
set_target_properties("${TARGET_NAME}" PROPERTIES CXX_STANDARD 20
                                                  CXX_STANDARD_REQUIRED ON
                                                  CXX_EXTENSIONS OFF
                                                  OUTPUT_NAME "${EXEC_NAME}"
)

target_include_directories("${TARGET_NAME}" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}"
                                                    "${ART_CXX_DEPS_DIR}/googletest/include"
                                                    "/opt/homebrew/opt/tbb/include"
                                                    "/opt/homebrew/opt/openssl/include"                                                 
)

target_sources("${TARGET_NAME}" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/tbb/tbb_test.cpp"
                                        "${CMAKE_CURRENT_SOURCE_DIR}/openssl/openssl_test.cpp"
)

target_compile_options("${TARGET_NAME}" PRIVATE -pthread 
                                                -ggdb
                                                -Wno-unused-value
                                                -Wno-unused-parameter
                                                -Wno-return-stack-address
                                                -Wno-tautological-undefined-compare
)

target_link_libraries("${TARGET_NAME}" PRIVATE -pthread  
                                               "${ART_CXX_DEPS_DIR}/googletest/lib/libgtest.a"
                                               "${ART_CXX_DEPS_DIR}/googletest/lib/libgmock.a"
                                               "/opt/homebrew/opt/tbb/lib/libtbb.a"
                                               "/opt/homebrew/opt/openssl/lib/libcrypto.a"
                                               "/opt/homebrew/opt/openssl/lib/libssl.a"
)