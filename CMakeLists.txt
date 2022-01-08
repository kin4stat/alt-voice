cmake_minimum_required (VERSION 2.8)

project(alt-voice)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/tools/cotire/CMake)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(cotire)

add_definitions(-DALT_LIB_STATIC)

file(GLOB_RECURSE PROJECT_SOURCE_FILES "src/*.h" "src/*.cpp" "include/*.h")

macro(GroupSources curdir groupindex)
  file(GLOB children RELATIVE ${curdir} ${curdir}/*)

  foreach(child ${children})
    if(IS_DIRECTORY ${curdir}/${child})
      GroupSources(${curdir}/${child} ${groupindex}/${child})
    else()

      string(REPLACE "/" "\\" groupname ${groupindex})

      source_group(${groupname} FILES ${curdir}/${child})
    endif()
  endforeach()
endmacro()

GroupSources(${PROJECT_SOURCE_DIR}/src "Source Files")
GroupSources(${PROJECT_SOURCE_DIR}/include "Include")

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
  RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/bin/Debug/"
  RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/bin/Release/"
)

cotire(${PROJECT_NAME})
