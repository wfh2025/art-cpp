set(TARGET_NAME "art-base")
set(OUTPUT_NAME "art_base")
set(SRCS 
    "${CMAKE_CURRENT_SOURCE_DIR}/art_str.cpp"
)
set(INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}")
set(COMPILE_OPTIONS -pthread -ggdb -Wno-unused-value 
                    -Wno-unused-parameter 
                    -Wno-return-stack-address 
                    -Wno-tautological-undefined-compare
)

add_library("${TARGET_NAME}-static" STATIC "${SRCS}")
set_target_properties("${TARGET_NAME}-static" PROPERTIES CXX_STANDARD 20
                                                  CXX_STANDARD_REQUIRED ON
                                                  CXX_EXTENSIONS OFF
                                                  VERSION "1.0.0"
                                                  OUTPUT_NAME "${OUTPUT_NAME}"
)

target_include_directories("${TARGET_NAME}-static" PRIVATE "${INCLUDE_DIRS}")
target_compile_options("${TARGET_NAME}-static" PRIVATE "${COMPILE_OPTIONS}")
target_link_libraries("${TARGET_NAME}-static" PRIVATE -pthread  
                                               "${ART_CXX_DEPS_DIR}/googletest/lib/libgtest.a"
)

add_library("${TARGET_NAME}-shared" SHARED "${SRCS}")
set_target_properties("${TARGET_NAME}-shared" PROPERTIES CXX_STANDARD 20
                                                  CXX_STANDARD_REQUIRED ON
                                                  CXX_EXTENSIONS OFF
                                                  OUTPUT_NAME "${OUTPUT_NAME}"
)

target_include_directories("${TARGET_NAME}-shared" PRIVATE "${INCLUDE_DIRS}")
target_compile_options("${TARGET_NAME}-shared" PRIVATE "${COMPILE_OPTIONS}")
target_link_libraries("${TARGET_NAME}-shared" PRIVATE -pthread  
                                               "${ART_CXX_DEPS_DIR}/googletest/lib/libgtest.a"
)