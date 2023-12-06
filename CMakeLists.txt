cmake_minimum_required(VERSION 3.23)

project(scc_mod LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(ConfigureVersionFromGit)
include(ConfigureDefaultOutputDirectories)
include(TargetOutputDirectory)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Steam/steamapps/common/Cyberpunk 2077/tools/redmod/")

configure_version_from_git()
configure_default_output_directories()

add_compile_definitions(
  # Support Windows 7 and above.
  WINVER=0x0601
  _WIN32_WINNT=0x0601

  # Exclude unnecessary APIs.
  WIN32_LEAN_AND_MEAN

  # Use Unicode charset.
  UNICODE
  _UNICODE
  GIT_VERSION_MAJOR=GIT_VERSION_MAJOR
  GIT_VERSION_MINOR=GIT_VERSION_MINOR
  GIT_VERSION_PATCH=GIT_VERSION_PATCH
  GIT_VERSION_STR_FULL=GIT_VERSION_STR_FULL
)

add_compile_options(
  # Enable correct reporting of C++ version, see https://docs.microsoft.com/en-us/cpp/build/reference/zc-cplusplus.
  $<$<BOOL:MSVC>:/Zc:__cplusplus>
)

add_link_options(
  /INCREMENTAL:NO
  /NATVIS:${CMAKE_SOURCE_DIR}/.natvis
)

include(ConfigureAndIncludeDetours)
include(ConfigureAndIncludeFmt)
# include(ConfigureAndIncludeRED4extSdk)
# include(ConfigureAndIncludeSpdlog)
# include(ConfigureAndIncludeToml11)
# include(ConfigureAndIncludeTslOrderedMap)
include(ConfigureAndIncludeWil)

add_subdirectory(src)

add_custom_target(compile
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_INSTALL_PREFIX}/bin/redlexer_native.dll ${CMAKE_INSTALL_PREFIX}/bin/redlexer_native_real.dll
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:redlexer_native.dll> ${CMAKE_INSTALL_PREFIX}/bin/redlexer_native.dll
  COMMAND "${CMAKE_INSTALL_PREFIX}/bin/scc.exe" -compile "scripts\\" "final.redscripts" -rttiSchemaPath "metadata.json" -Wnone -threads 4 -no-testonly -no-breakpoint -profile=off 
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_INSTALL_PREFIX}/bin/redlexer_native_real.dll ${CMAKE_INSTALL_PREFIX}/bin/redlexer_native.dll
  WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}
  DEPENDS redlexer_native.dll)

add_custom_target(decompile 
  COMMAND "D:/Code/redscript/target/release/redscript-cli.exe" decompile -i "${CMAKE_INSTALL_PREFIX}/final.redscripts" -o "redscripts" -m code -f
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)