cmake_minimum_required(VERSION 2.8.12)

set(TARGET_NAME boilerplate)
project(${TARGET_NAME})

# Register the Out-Of-Tree extension
if (NOT DEFINED DUCKDB_OOTE_EXTENSION_NAMES)
    set(DUCKDB_OOTE_EXTENSION_NAMES "" PARENT_SCOPE)
endif()
list(APPEND DUCKDB_OOTE_EXTENSION_NAMES ${TARGET_NAME})
set(DUCKDB_OOTE_EXTENSION_${TARGET_NAME}_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(DUCKDB_OOTE_EXTENSION_${TARGET_NAME}_SHOULD_LINK TRUE)

# Now all we need is the Duck!
add_subdirectory(duckdb)