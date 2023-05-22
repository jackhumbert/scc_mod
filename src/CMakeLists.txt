add_library(redlexer_native.dll SHARED)

set_target_properties(redlexer_native.dll PROPERTIES OUTPUT_NAME redlexer_native)

file(GLOB_RECURSE HEADER_FILES *.hpp)
file(GLOB_RECURSE SOURCE_FILES *.cpp)
file(GLOB_RECURSE DEF_FILES *.def)
file(GLOB_RECURSE RC_FILES *.rc)

source_group(_CMake REGULAR_EXPRESSION cmake_pch.*)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HEADER_FILES} ${SOURCE_FILES} ${DEF_FILES} ${RC_FILES})

target_include_directories(redlexer_native.dll PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(redlexer_native.dll PRIVATE ${HEADER_FILES} ${SOURCE_FILES} ${DEF_FILES} ${RC_FILES})

target_precompile_headers(redlexer_native.dll PRIVATE stdafx.hpp)
target_link_libraries(redlexer_native.dll PRIVATE fmt WIL)