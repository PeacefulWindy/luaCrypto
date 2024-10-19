cmake_minimum_required(VERSION 3.25)

project(luaCrypto)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

set(platform "windows")
#set(platform "linux")

if(${platform} MATCHES "windows")
    set(VCPKG_TARGET_TRIPLET x64-windows)
elseif(${platform} MATCHES "linux")
    set(VCPKG_TARGET_TRIPLET x64-linux)
endif()

if(${CMAKE_HOST_SYSTEM_NAME} MATCHES "Windows")
    if(CMAKE_BUILD_TYPE MATCHES "Debug")
        set(VCPKG_INSTALL_ROOT ${CMAKE_SOURCE_DIR}/out/build/x64-Debug/vcpkg_installed/${VCPKG_TARGET_TRIPLET})
    else()
        set(VCPKG_INSTALL_ROOT ${CMAKE_SOURCE_DIR}/out/build/x64-Release/vcpkg_installed/${VCPKG_TARGET_TRIPLET})
    endif()
else()
    set(VCPKG_INSTALL_ROOT ${CMAKE_SOURCE_DIR}/vcpkg_installed)
endif()

if(CMAKE_BUILD_TYPE MATCHES "Debug")
    link_directories(${VCPKG_INSTALL_ROOT}/debug/lib)
else()
    link_directories(${VCPKG_INSTALL_ROOT}/lib)
endif()

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${VCPKG_INSTALL_ROOT}/include)

set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE})

aux_source_directory(src srcs)
aux_source_directory(src/util srcs)
aux_source_directory(src/base64 srcs)
aux_source_directory(src/rsa srcs)
aux_source_directory(src/sha srcs)

find_package(lua REQUIRED)
find_package(cryptopp CONFIG REQUIRED)

add_library(${PROJECT_NAME} SHARED ${srcs} ${LUA_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE cryptopp::cryptopp lua)