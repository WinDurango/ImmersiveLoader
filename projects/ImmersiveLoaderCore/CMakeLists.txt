cmake_minimum_required(VERSION 4.0)
project(ImmersiveLoaderCore VERSION 1.0.0)

set(VERSION_SUFFIX "-dev.1") # used for non-stable versions, otherwise blank
set(CMAKE_CXX_STANDARD 23)

find_package(pugixml CONFIG REQUIRED HINTS "${CMAKE_SOURCE_DIR}/vcpkg_installed/arm64-windows/share/pugixml")

add_compile_definitions(WD_API_EXPORTS)

set(FILES
    src/ImmersiveLoaderCore.cpp
)

add_library(ImmersiveLoaderCore SHARED ${FILES})
target_include_directories(ImmersiveLoaderCore PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
)

target_link_libraries(ImmersiveLoaderCore PUBLIC pugixml::shared pugixml::pugixml)

target_compile_definitions(ImmersiveLoaderCore PUBLIC
    WINDURANGO_IMMERSIVELOADER_CORE_COMPILER_NAME="${CMAKE_CXX_COMPILER_ID}"
    WINDURANGO_IMMERSIVELOADER_CORE_PLATFORM_NAME="${CMAKE_SYSTEM_NAME}"
    WINDURANGO_IMMERSIVELOADER_CORE_PLATFORM_ARCH="${CMAKE_SYSTEM_PROCESSOR}"
    WINDURANGO_IMMERSIVELOADER_CORE_VERSION="${PROJECT_VERSION}${VERSION_SUFFIX}"
    WINDURANGO_IMMERSIVELOADER_CORE_RC_VERSION=${PROJECT_VERSION_MAJOR},${PROJECT_VERSION_MINOR},${PROJECT_VERSION_PATCH}
)

set_target_properties(ImmersiveLoaderCore PROPERTIES LINKER_LANGUAGE CXX)