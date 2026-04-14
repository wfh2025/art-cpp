set(TARGET_NAME "art-s3")
set(OUTPUT_NAME "art_s3")

find_package(LibreSSL CONFIG REQUIRED PATHS "${ART_CXX_DEPS_DIR}/libressl" NO_DEFAULT_PATH)

find_package(civetweb CONFIG REQUIRED PATHS "${ART_CXX_DEPS_DIR}/civetweb" NO_DEFAULT_PATH)
find_package(pugixml CONFIG REQUIRED PATHS "${ART_CXX_DEPS_DIR}/pugixml" NO_DEFAULT_PATH)
find_package(spdlog CONFIG REQUIRED PATHS "${ART_CXX_DEPS_DIR}/spdlog" NO_DEFAULT_PATH)

set(SRCS "${CMAKE_CURRENT_SOURCE_DIR}/s3_algs.cpp"  
         "${CMAKE_CURRENT_SOURCE_DIR}/s3_auth.cpp" 
         "${CMAKE_CURRENT_SOURCE_DIR}/s3_base.cpp"
         "${CMAKE_CURRENT_SOURCE_DIR}/s3_def.cpp"
         "${CMAKE_CURRENT_SOURCE_DIR}/s3_error.cpp"
         "${CMAKE_CURRENT_SOURCE_DIR}/s3_http.cpp"
         "${CMAKE_CURRENT_SOURCE_DIR}/s3_model.cpp"
         "${CMAKE_CURRENT_SOURCE_DIR}/s3_req.cpp"
         "${CMAKE_CURRENT_SOURCE_DIR}/s3_resp.cpp"
         "${CMAKE_CURRENT_SOURCE_DIR}/s3_route.cpp"
         "${CMAKE_CURRENT_SOURCE_DIR}/s3_svc.cpp"
         "${CMAKE_CURRENT_SOURCE_DIR}/s3_utils.cpp"
)
set(INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}"
                 "${CMAKE_SOURCE_DIR}"
                 "${LIBRESSL_INCLUDE_DIR}"
)
set(COMPILE_OPTIONS -pthread -ggdb -Wno-unused-value 
                    -Wno-unused-parameter
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
target_compile_definitions("${TARGET_NAME}-static" PRIVATE 
                            SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG
)
target_link_libraries("${TARGET_NAME}-static" PRIVATE -pthread  
                                                LibreSSL::Crypto
                                                pugixml::pugixml
                                                spdlog::spdlog
                                                civetweb::civetweb-cpp
)

add_library("${TARGET_NAME}-shared" SHARED "${SRCS}")
set_target_properties("${TARGET_NAME}-shared" PROPERTIES CXX_STANDARD 20
                                                  CXX_STANDARD_REQUIRED ON
                                                  CXX_EXTENSIONS OFF
                                                  OUTPUT_NAME "${OUTPUT_NAME}"
)
target_include_directories("${TARGET_NAME}-shared" PRIVATE "${INCLUDE_DIRS}")
target_compile_options("${TARGET_NAME}-shared" PRIVATE "${COMPILE_OPTIONS}")
target_compile_definitions("${TARGET_NAME}-shared" PRIVATE 
                            SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG
)
target_link_libraries("${TARGET_NAME}-shared" PRIVATE -pthread  
                                                LibreSSL::Crypto
                                                pugixml::pugixml
                                                spdlog::spdlog
                                                civetweb::civetweb-cpp
)