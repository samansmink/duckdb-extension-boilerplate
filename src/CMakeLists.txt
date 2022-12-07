cmake_minimum_required(VERSION 2.8.12)

# Set extension name here
set(TARGET_NAME boilerplate)

set(EXTENSION_NAME ${TARGET_NAME}_extension)
set(LOADABLE_EXTENSION_NAME ${TARGET_NAME}_loadable_extension)

# TODO should this be in the boilerplate?
if (OSX_BUILD_UNIVERSAL EQUAL 1)
    set(OSX_UNIVERSAL_FLAG -DCMAKE_OSX_ARCHITECTURES=x86_64$<SEMICOLON>arm64)
else()
    set(OSX_UNIVERSAL_FLAG "")
endif()

project(${TARGET_NAME})

include_directories(include)
include_directories(../..)

set(EXTENSION_SOURCES boilerplate_extension.cpp)

add_library(${EXTENSION_NAME} STATIC ${EXTENSION_SOURCES})

set(PARAMETERS "-warnings")

build_loadable_extension(${TARGET_NAME} ${PARAMETERS} ${EXTENSION_SOURCES})

install(
  TARGETS ${EXTENSION_NAME}
  EXPORT "${DUCKDB_EXPORT_SET}"
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}"
  ARCHIVE DESTINATION "${INSTALL_LIB_DIR}")