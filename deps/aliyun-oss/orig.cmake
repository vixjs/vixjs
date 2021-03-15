#
# Copyright 2009-2017 Alibaba Cloud All rights reserved.
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#      http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

include(${CMAKE_CURRENT_SOURCE_DIR}/pre.cmake)

project(cpp-sdk VERSION ${version})

configure_file(src/Config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/include/alibabacloud/oss/Config.h @ONLY)

#common header
file(GLOB sdk_auth_header "include/alibabacloud/oss/auth/*.h")
file(GLOB sdk_client_header "include/alibabacloud/oss/client/*.h")
file(GLOB sdk_http_header "include/alibabacloud/oss/http/*.h")
file(GLOB sdk_utils_header "include/alibabacloud/oss/utils/*.h")
file(GLOB sdk_model_header "include/alibabacloud/oss/model/*.h")
file(GLOB sdk_encryption_header "include/alibabacloud/oss/encryption/*.h")
file(GLOB sdk_public_header "include/alibabacloud/oss/*.h")

#all header
file(GLOB sdk_header
    ${sdk_auth_header}
    ${sdk_client_header}
    ${sdk_http_header}
    ${sdk_utils_header}
    ${sdk_model_header}
    ${sdk_encryption_header}
    ${sdk_public_header}
)

#common source
file(GLOB sdk_auth_src "src/auth/*.cc")
file(GLOB sdk_client_src "src/client/*.cc")
file(GLOB sdk_http_src "src/http/*.cc")
file(GLOB sdk_utils_src "src/utils/*.cc")
file(GLOB sdk_public_src "src/*.cc")

#add source by DISABLE_XX option
file(GLOB sdk_model_common_src 
	"src/model/ModelError.cc"
)

if (NOT OSS_DISABLE_BUCKET)
file(GLOB sdk_model_bucket_src 
	"src/model/*Bucket*.cc"
	"src/model/GetUserQos*.cc"
	"src/model/LifecycleRule.cc"
	"src/model/InventoryConfiguration.cc"
	"src/model/Tagging.cc"
)
endif()

file(GLOB sdk_model_object_src 
	"src/model/*Object*.cc"
	"src/model/*Symlink*.cc"
	"src/model/InputFormat.cc"
	"src/model/OutputFormat.cc"
	"src/model/Tagging.cc"
	"src/model/GeneratePresignedUrlRequest.cc"
)

file(GLOB sdk_model_multipart_src 
	"src/model/*MultipartUpload*.cc"
	"src/model/UploadPart*.cc"
	"src/model/ListPart*.cc"
)

if (NOT OSS_DISABLE_LIVECHANNEL)
file(GLOB sdk_model_livechannel_src 
	"src/model/*LiveChannel*.cc"
	"src/model/GetVod*.cc"
	"src/model/PostVod*.cc"
	"src/model/GenerateRTMPSignedUrlRequest.cc"
)
endif()

file(GLOB sdk_model_src
	${sdk_model_common_src}
	${sdk_model_bucket_src}
	${sdk_model_object_src}
	${sdk_model_multipart_src}
	${sdk_model_livechannel_src}
)

if (NOT OSS_DISABLE_RESUAMABLE)
file(GLOB sdk_resumable_src "src/resumable/*.cc")
endif()

if (NOT OSS_DISABLE_ENCRYPTION)
file(GLOB sdk_encryption_src "src/encryption/*.cc")
endif()

#external source
file(GLOB sdk_external_tinnyxml2_src "src/external/tinyxml2/*.cpp")

if (NOT OSS_DISABLE_ENCRYPTION OR NOT OSS_DISABLE_RESUAMABLE)
file(GLOB sdk_external_json_src "src/external/json/*.cpp")
endif()


#all source
file(GLOB sdk_src
    ${sdk_auth_src}
    ${sdk_client_src}
    ${sdk_http_src}
    ${sdk_utils_src}
    ${sdk_model_src}
    ${sdk_public_src}
    ${sdk_resumable_src}
    ${sdk_encryption_src}
    ${sdk_external_json_src}
    ${sdk_external_tinnyxml2_src}
)

#extra define pass to source code
if (BUILD_TESTS)
    set(EXTRA_DEFINE "-DENABLE_OSS_TEST")
else()
    set(EXTRA_DEFINE "")
endif()
    
#static lib
add_library(${name} STATIC
    ${sdk_header}
    ${sdk_src})

target_include_directories(
    ${name}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/alibabacloud/oss    
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/external/
)

target_include_directories(
    ${name}
    PRIVATE ${CRYPTO_INCLUDE_DIRS}
    PRIVATE ${CLIENT_INCLUDE_DIRS}
)

# target_link_libraries(${name} ${CRYPTO_LIBS} ${CLIENT_LIBS})

target_compile_options(${name} 
    PRIVATE "${SDK_COMPILER_FLAGS}" "${EXTRA_DEFINE}")