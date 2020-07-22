cmake_minimum_required(VERSION 3.13.0)

project(CPPExamples VERSION 1.0
  DESCRIPTION "A collection of examples for practicing Modern C++ concepts"
  LANGUAGES CXX C
  )

if(WIN32)
  add_compile_options(/Wall /Wextra /Wpedantic)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

if(APPLE)
  cmake_minimum_required(VERSION 3.16.0)
endif()
find_package(Threads REQUIRED)

add_executable(MatrixExample)
add_executable(BindExample)
add_executable(StringLiteralsExample)
add_executable(RAIIAndSmartExample)
add_executable(InheritanceExample)
add_executable(StructuredBindingExample)
add_executable(RegexAndFilesystemExample)
add_executable(AsyncExample)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(src)


target_link_libraries(AsyncExample PUBLIC Threads::Threads)
