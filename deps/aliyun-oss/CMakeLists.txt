cmake_minimum_required(VERSION 2.6)

set(name "aliyun-oss")
project(${name})

include(${CMAKE_CURRENT_SOURCE_DIR}/orig.cmake)

include(${CMAKE_CURRENT_SOURCE_DIR}/../../vender/tools/option.cmake)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../../../bin/${CMAKE_HOST_SYSTEM_NAME}_${ARCH}_${BUILD_TYPE})

setup_result_library(${name})