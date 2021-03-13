cmake_minimum_required(VERSION 3.0)

if(NOT "${CLEAN_BUILD}" STREQUAL "true")
    include(../vender/tools/get_env.cmake)

    set(libs
        aliyun-oss
    )

    set(WORK_ROOT $ENV{WORK_ROOT})
    if(NOT WORK_ROOT)
        set(WORK_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/..")
    endif()

    set(BIN_ROOT "${WORK_ROOT}/bin")
    set(OUT_ROOT "${WORK_ROOT}/out")
    set(DIST_DIRNAME "${CMAKE_HOST_SYSTEM_NAME}_${BUILD_ARCH}_${BUILD_TYPE}")

    if("${CLEAN_BUILD}" STREQUAL "true")
        rimraf(${BIN_ROOT}/${DIST_DIRNAME})
        rimraf(${OUT_ROOT}/${DIST_DIRNAME})
    else()
        set(OUT_PATH "${OUT_ROOT}/${DIST_DIRNAME}")

        foreach(lib ${libs})
            build("${CMAKE_CURRENT_SOURCE_DIR}/${lib}" "${OUT_PATH}/${lib}")
        endforeach()

        foreach(lib ${libs})
            if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${lib}/test")
                build("${CMAKE_CURRENT_SOURCE_DIR}/${lib}/test" "${OUT_PATH}/${lib}_test")
            endif()
        endforeach()
    endif()
endif()
