cmake_minimum_required(VERSION 2.8)
project(spell-checker)

find_package(Boost 1.58.0 COMPONENTS serialization REQUIRED)

include_directories(${Boost_INCLUDE_DIRS}) 

set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++14 ")

set(CMAKE_AR  "gcc-ar")
set(CMAKE_CXX_ARCHIVE_CREATE "<CMAKE_AR> qcs <TARGET> <LINK_FLAGS> <OBJECTS>")
set(CMAKE_CXX_ARCHIVE_FINISH   true)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -ggdb3")
#-fprofile-generate and -fprofile-use
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -pedantic -march=native -Ofast -fprofile-generate -frename-registers -funroll-loops -flto -pg")

file(GLOB SRC
  "src/test_trie.cc"
)

add_subdirectory(src/trie)
add_subdirectory(src/utils)

IF(CMAKE_BUILD_TYPE MATCHES Release)
   message("Release mode")

  add_executable(TextMiningCompiler_pass1 src/test_trie.cc
     $<TARGET_OBJECTS:trie>
     $<TARGET_OBJECTS:utils>)

  add_executable(TextMiningCompiler src/test_trie.cc
    $<TARGET_OBJECTS:trie>
    $<TARGET_OBJECTS:utils>)

  set_target_properties(TextMiningCompiler PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS}  -fprofile-use")

  add_custom_target(TextMiningCompiler_pass2
    COMMAND time ./TextMiningCompiler_pass1 "subject/words.txt"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Profiling the TextMiningCompiler"
  )
  add_dependencies(TextMiningCompiler TextMiningCompiler_pass2)

ENDIF(CMAKE_BUILD_TYPE MATCHES Release)

IF(CMAKE_BUILD_TYPE MATCHES Debug)
  message("Debug mode")
  add_executable(TextMiningCompiler src/test_trie.cc
     $<TARGET_OBJECTS:trie>
     $<TARGET_OBJECTS:utils>)
 ENDIF(CMAKE_BUILD_TYPE MATCHES Debug)

add_custom_target(deep_clean
  COMMAND find . -iwholename '*cmake*' -not -name CMakeLists.txt -not -name cmake_deps -not -name '*Find*' -delete
  COMMAND find . -iwholename '*Makefile*' -delete
)
