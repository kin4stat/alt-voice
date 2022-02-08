cmake_minimum_required (VERSION 3.16)

project(alt-voice)

include("tools/cotire/CMake/cotire.cmake")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

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

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/include)

target_compile_definitions(${PROJECT_NAME} PUBLIC ALT_LIB_STATIC)

find_package(Opus CONFIG REQUIRED)

if (WIN32)
target_link_libraries(${PROJECT_NAME} PRIVATE WinMM.lib)
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC OpenAL)
target_link_libraries(${PROJECT_NAME} PUBLIC Opus::opus)

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
