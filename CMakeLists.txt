cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    cloxc
    VERSION 0.1.0
    DESCRIPTION "Lox C implementation"
    LANGUAGES C
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(
    cloxc_lib OBJECT
    source/table.c
    source/object.c
    source/scanner.c
    source/compiler.c
    source/vm.c
    source/value.c
    source/chunk.c
    source/memory.c
    source/debug.c
    source/lib.c
)

target_include_directories(
    cloxc_lib ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

target_compile_features(cloxc_lib PUBLIC c_std_11)

# ---- Declare executable ----

add_executable(cloxc_exe source/main.c)
add_executable(cloxc::exe ALIAS cloxc_exe)

set_property(TARGET cloxc_exe PROPERTY OUTPUT_NAME cloxc)

target_compile_features(cloxc_exe PRIVATE c_std_11)

target_link_libraries(cloxc_exe PRIVATE cloxc_lib)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT cloxc_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of cloxc"
  )
endif()

include(cmake/dev-mode.cmake)

if(CMAKE_C_COMPILER_ID MATCHES "Clang") 
  target_compile_options(cloxc_lib PRIVATE -Wno-float-equal)
  target_compile_options(cloxc_exe PRIVATE -Wno-float-equal)
endif()