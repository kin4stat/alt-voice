cmake_minimum_required (VERSION 2.8)

project(alt-voice)

include("tools/cotire/CMake/cotire.cmake")

add_definitions(-DALT_LIB_STATIC)

file(GLOB_RECURSE PROJECT_SOURCE_FILES "src/*.h" "src/*.cpp" "include/*.h")

include_directories(
  ${PROJECT_SOURCE_DIR}/src
  ${PROJECT_SOURCE_DIR}/include
)

add_library(
  ${PROJECT_NAME} STATIC
  ${PROJECT_SOURCE_FILES}
)

find_package(Opus CONFIG REQUIRED)
find_package(OpenAL CONFIG REQUIRED)

if (WIN32)
target_link_libraries(${PROJECT_NAME} PRIVATE WinMM.lib)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE OpenAL::OpenAL)
target_link_libraries(${PROJECT_NAME} PRIVATE Opus::opus)

#Tests
if(BUILD_TESTS)
  add_executable(
    3d-two-sources
    ${PROJECT_SOURCE_DIR}/examples/3d-two-sources.cpp
  )
  if (WIN32)
  target_link_libraries(3d-two-sources WinMM.lib)
  endif()
  target_link_libraries(3d-two-sources alt-voice)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
  CXX_STANDARD 17
)

cotire(${PROJECT_NAME})
