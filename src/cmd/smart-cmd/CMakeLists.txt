set(TARGET_NAME "art-cmd-smart-cmd")
set(EXEC_NAME "smart-cmd")

add_executable("${TARGET_NAME}" "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
set_target_properties("${TARGET_NAME}" PROPERTIES CXX_STANDARD 20
                                                CXX_STANDARD_REQUIRED ON
                                                CXX_EXTENSIONS OFF
                                                OUTPUT_NAME "${EXEC_NAME}"
)
target_include_directories("${TARGET_NAME}" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}"
                                                  "${DEPS_DIR}/fmt/include"
                                                  "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/deps/linenoise"
                                                  "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/deps/lua/src"
                                                  "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/src"
                                                  "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/deps/fpconv"
                                                  "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/deps/hiredis"
                                                  "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/deps/hdr_histogram"
)
target_sources("${TARGET_NAME}" PRIVATE "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/deps/linenoise/linenoise.c"
                                      "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/src/zmalloc.c"
                                      "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/deps/fpconv/fpconv_dtoa.c"
                                      "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/src/sha256.c"
                                      "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/src/util.c"
                                      "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/src/sds.c"
                                      "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/src/adlist.c"
                                      "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/src/crc16.c"
                                      "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/src/crc64.c"
                                      "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/src/crcspeed.c"
                                      "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/src/sha1.c"
                                      "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/src/siphash.c"
                                      "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/src/rax.c"
                                      "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/src/rand.c"
                                      "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/src/mt19937-64.c"
                                      "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/src/redisassert.c"
                                      "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/src/dict.c"
                                      "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/src/setcpuaffinity.c"
                                      "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/src/setproctitle.c"
                                      "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/src/sparkline.c"
                                      "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/src/strl.c"
                                      "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/src/zipmap.c"
                                      "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/src/ziplist.c"
                                      "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/src/pqsort.c"
                                      "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/src/monotonic.c"
                                      "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/src/memtest.c"
                                      "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/src/lzf_c.c"
                                      "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/src/lzf_d.c"
                                      "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/src/localtime.c"
                                      "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/src/listpack.c"
                                      "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/src/intset.c"
                                      "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/src/endianconv.c"
                                      "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/src/geohash.c"
                                      "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/src/geohash_helper.c"
                                      "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/src/cli_commands.c"
                                      "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/src/anet.c"
                                      "${CMAKE_SOURCE_DIR}/third-party/redis-7.2.11/src/rio.c"                         
)
target_compile_options("${TARGET_NAME}" PRIVATE -pthread 
                                              -ggdb
                                              -Wno-unused-parameter
)
target_link_libraries("${TARGET_NAME}" PRIVATE -pthread 
                                             "${ART_CXX_DEPS_DIR}/fmt/lib/libfmt.a"
)