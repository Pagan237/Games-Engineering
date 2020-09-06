cmake_minimum_required(VERSION 3.9)

# Set compiler flags
if (MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /EHsc" CACHE INTERNAL "" FORCE)
elseif(APPLE)
  set(CMAKE_OSX_DEPLOYMENT_TARGET 10.9 CACHE STRING "")
  set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")
endif()

# Require modern C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Games_Engineering)

### Setup Directories ###
# Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Output all DLLs from all libs into main build folder
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

### Add External Deps ###
# SFML - graphics library
add_subdirectory("lib/sfml" EXCLUDE_FROM_ALL)
#include_directories("lib/sfml/include")
set(SFML_INCS "lib/sfml/include")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")



file(GLOB_RECURSE RESOURCE_FILES "res/*.*")
####
file(GLOB_RECURSE SOURCE_FILES engine/src/*.cpp engine/src/*.h)
add_library(engine_lib STATIC ${SOURCE_FILES} ${RESOURCE_FILES})
target_include_directories(engine_lib INTERFACE "${CMAKE_SOURCE_DIR}/engine/src/" PUBLIC SYSTEM ${B2D_INCS})
target_link_libraries(engine_lib maths_lib ecm_lib lib_tile_level_loader sfml-graphics sfml-audio)


## Maths lib
add_library(maths_lib INTERFACE)
target_sources(maths_lib INTERFACE "${CMAKE_SOURCE_DIR}/engine/maths_lib/maths.h")
target_include_directories(maths_lib INTERFACE "${CMAKE_SOURCE_DIR}/engine/maths_lib" INTERFACE ${SFML_INCS})

## ECM lib
file(GLOB_RECURSE SOURCE_FILES engine/ecm_lib/*.cpp engine/ecm_lib/*.h)
add_library(ecm_lib STATIC ${SOURCE_FILES})
target_include_directories(ecm_lib INTERFACE "${CMAKE_SOURCE_DIR}/engine/ecm_lib" )
target_link_libraries(ecm_lib PRIVATE maths_lib)

# Tile Loader
file(GLOB_RECURSE SOURCE_FILES engine/lib_tile_level_loader/*.cpp engine/lib_tile_level_loader/*.h)
add_library(lib_tile_level_loader STATIC ${SOURCE_FILES} ${RESOURCE_FILES})
target_include_directories(lib_tile_level_loader INTERFACE "${CMAKE_SOURCE_DIR}/engine/lib_tile_level_loader/" )
target_link_libraries(lib_tile_level_loader maths_lib sfml-graphics)

## 6 - Platformer
file(GLOB_RECURSE SOURCES source/*.cpp source/*.h)
file(GLOB_RECURSE CMPNTS source/components/*.cpp source/components/*.h)
file(GLOB_RECURSE SCENES source/scenes/*.cpp source/scenes/*.h)
add_executable(GAME ${SOURCES} ${RESOURCE_FILES})
source_group("components" FILES ${CMPNTS})
source_group("resources" FILES ${RESOURCE_FILES})
target_include_directories(GAME SYSTEM PRIVATE ${SFML_INCS} )
target_link_libraries(GAME engine_lib)
set(EXECUTABLES ${EXECUTABLES} GAME)
