cmake_minimum_required(VERSION 3.0)

if(NOT "${CLEAN_BUILD}" STREQUAL "true")
    include(../../vender/build_tools/cmake-scripts/get_env.cmake)

    set(WORK_ROOT $ENV{WORK_ROOT})
    if(NOT WORK_ROOT)
        set(WORK_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../..")
    endif()

    set(BIN_PATH "${WORK_ROOT}/bin/${CMAKE_HOST_SYSTEM_NAME}_${BUILD_ARCH}_${BUILD_TYPE}")

    if(${BUILD_TYPE} STREQUAL "release")
        if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
            execute_process(WORKING_DIRECTORY ${BIN_PATH} COMMAND fibjs ${CMAKE_CURRENT_SOURCE_DIR}/gen_install.js)
            set(OUT_PATH "${WORK_ROOT}/out/${CMAKE_HOST_SYSTEM_NAME}_${BUILD_ARCH}_${BUILD_TYPE}")
            build("${CMAKE_CURRENT_SOURCE_DIR}" "${OUT_PATH}/installer")

            execute_process(COMMAND dumpbin /dependents ${BIN_PATH}/fibjs.exe)
        else()
            execute_process(WORKING_DIRECTORY ${BIN_PATH} COMMAND ${CMAKE_COMMAND} -E tar -zcf fibjs.tar.gz fibjs)
            message("[100%] Built target fibjs.tar.gz")

            execute_process(OUTPUT_FILE ${BIN_PATH}/installer.sh
                COMMAND cat ${CMAKE_CURRENT_SOURCE_DIR}/src/installer.txt ${BIN_PATH}/fibjs.tar.gz)
            execute_process(COMMAND chmod 777 ${BIN_PATH}/installer.sh)
            message("[100%] Built target install.sh")

            if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")
                if(${BUILD_ARCH} STREQUAL "arm")
                    set(BUILD_PREFIX "arm-linux-gnueabihf-")
                elseif(${BUILD_ARCH} STREQUAL "arm64")
                    set(BUILD_PREFIX "aarch64-linux-gnu-")
                elseif(${BUILD_ARCH} STREQUAL "mips")
                    set(BUILD_PREFIX "mips-linux-gnu-")
                elseif(${BUILD_ARCH} STREQUAL "mips64")
                    set(BUILD_PREFIX "mips64-linux-gnuabi64-")
                elseif(${BUILD_ARCH} STREQUAL "ppc")
                    set(BUILD_PREFIX "powerpc-linux-gnu-")
                elseif(${BUILD_ARCH} STREQUAL "ppc64")
                    set(BUILD_PREFIX "powerpc64-linux-gnu-")
                endif()

                message("")
                message("==== GLIBC ====")
                execute_process(COMMAND ${BUILD_PREFIX}objdump ${BIN_PATH}/fibjs -p COMMAND grep GLIBCX*_[0-9.]* -o COMMAND sort COMMAND uniq)
            endif()

            message("ENV:CI is $ENV{CI}")
            if(NOT "$ENV{CI}" STREQUAL "")
                execute_process(OUTPUT_FILE ${BIN_PATH}/fibjs.xz
                    COMMAND xz -cz -T2 ${BIN_PATH}/fibjs)
                message("[100%] Built target fibjs.xz")
            endif()
        endif()
    endif()
endif()
