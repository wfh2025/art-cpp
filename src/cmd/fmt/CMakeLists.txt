set(TARGET_NAME "fmt")
set(EXEC_NAME "fmt-demo") # 可执行文件名称
set(DEPS_DIR ${CMAKE_SOURCE_DIR}/../deps)
file(GLOB SRC "*.cpp" "*.cxx" "*.cc" "*.c")
file(GLOB DEPS_LIBS "${DEPS_DIR}/fmt/lib/*.a")

add_executable(${TARGET_NAME} ${SRC})
set_target_properties(${TARGET_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED OFF
    CXX_EXTENSIONS OFF
    OUTPUT_NAME "${EXEC_NAME}"
)

target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} 
                                                ${DEPS_DIR}/fmt/include)
# target_link_directories(${TARGET_NAME} PRIVATE "${DEPS_DIR}/fmt/lib")
target_link_libraries(${TARGET_NAME} PRIVATE ${DEPS_LIBS})
target_compile_options(${TARGET_NAME} PRIVATE 
    -ggdb
    -Wno-unused-parameter
)