set(TARGET_NAME "cv")
set(EXEC_NAME "cv-demo")
file(GLOB SRC "*.cpp" "*.cxx" "*.cc" "*.c")

find_package(OpenCV REQUIRED)

add_executable(${TARGET_NAME} ${SRC})
set_target_properties(${TARGET_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED OFF
    CXX_EXTENSIONS OFF
    OUTPUT_NAME "${EXEC_NAME}"
)
target_include_directories(${TARGET_NAME} PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(${TARGET_NAME} PRIVATE ${OpenCV_LIBS})
target_compile_options(${TARGET_NAME} PRIVATE 
    -Wall
    -Wextra
    -ggdb
)