cmake_minimum_required(VERSION 2.8)
project(spell-checker)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++11 -pedantic -ggdb3")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -Werror -O3")

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
