set(TARGET_NAME "xml")
set(EXEC_NAME "xml-demo")
set(DEPS_DIR ${CMAKE_SOURCE_DIR}/../deps)
file(GLOB SRC "*.cpp" "*.cxx" "*.cc" "*.c")

include_directories(${DEPS_DIR}/pugixml/include)
link_directories(${DEPS_DIR}/pugixml/lib)

add_executable(${TARGET_NAME} ${SRC})
set_target_properties(${TARGET_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED OFF
    CXX_EXTENSIONS OFF
    OUTPUT_NAME "${EXEC_NAME}"
)
target_link_libraries(${TARGET_NAME} PRIVATE pugixml)
target_compile_options(${TARGET_NAME} PRIVATE 
    -ggdb
    -Wno-unused-parameter
)