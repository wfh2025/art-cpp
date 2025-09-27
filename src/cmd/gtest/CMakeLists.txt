set(TARGET_NAME "gtest-run")
set(EXEC_NAME "gtest-demo") # 可执行文件名称
set(DEPS_DIR ${CMAKE_SOURCE_DIR}/../deps)
file(GLOB SRC "*.cpp" "*.cxx" "*.cc" "*.c")
file(GLOB DEPS_LIBS "${DEPS_DIR}/abseil-cpp/lib/*.a" 
                    "${DEPS_DIR}/fmt/lib/*.a"
                    "${DEPS_DIR}/pugixml/lib/*.a"
                    "${DEPS_DIR}/abseil-cpp/lib/*.a")

add_executable(${TARGET_NAME} ${SRC})
set_target_properties(${TARGET_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED OFF
    CXX_EXTENSIONS OFF
    OUTPUT_NAME "${EXEC_NAME}"
)

target_include_directories(${TARGET_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}"
                                                "${DEPS_DIR}/googletest/include"
                                                "${DEPS_DIR}/fmt/include"
                                                "${DEPS_DIR}/pugixml/include"
                                                "${DEPS_DIR}/abseil-cpp/include"
                                                "${DEPS_DIR}/json/include")
# target_link_directories(${TARGET_NAME} PRIVATE "${DEPS_DIR}/googletest/lib")
target_link_libraries(${TARGET_NAME} PRIVATE "${DEPS_DIR}/googletest/lib/libgtest_main.a"
                                             "${DEPS_DIR}/googletest/lib/libgtest.a" 
                                             "${DEPS_DIR}/googletest/lib/libgmock.a"
                                             "${DEPS_LIBS}")
target_compile_options(${TARGET_NAME} PRIVATE 
    -ggdb
    -Wno-unused-parameter
)