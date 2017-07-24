cmake_minimum_required(VERSION 2.8)
project(spell-checker)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++14 ")

set(CMAKE_AR  "gcc-ar")
set(CMAKE_CXX_ARCHIVE_CREATE "<CMAKE_AR> qcs <TARGET> <LINK_FLAGS> <OBJECTS>")
set(CMAKE_CXX_ARCHIVE_FINISH   true)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -ggdb3")
#-fprofile-generate and -fprofile-use
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -pedantic -march=native -Ofast -frename-registers -funroll-loops -flto -pg")

file(GLOB SRC
  "src/text_mining_compiler.cc"
)

add_subdirectory(src/dawg)
add_subdirectory(src/utils)
add_executable(TextMiningCompiler src/text_mining_compiler.cc
  $<TARGET_OBJECTS:dawg>
  $<TARGET_OBJECTS:utils>)

add_custom_target(deep_clean
  COMMAND find . -iwholename '*cmake*' -not -name CMakeLists.txt -not -name cmake_deps -not -name '*Find*' -delete
  COMMAND find . -iwholename '*Makefile*' -delete
)
