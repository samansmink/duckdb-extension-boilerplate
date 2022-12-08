cmake_minimum_required(VERSION 2.8.12)

if(${CMAKE_PROJECT_NAME} STREQUAL DuckDB)
    # Building from within duckdb
    add_subdirectory(src)
else()
    # Building from extension,
    set(TARGET_NAME boilerplate)
    project(${TARGET_NAME})

    cmake_policy(SET CMP0079 NEW)

    include_directories(src/include)

    # Register this extension as OOTE in DuckDB build
    if (NOT DEFINED DUCKDB_OOTE_EXTENSION_NAMES)
        set(DUCKDB_OOTE_EXTENSION_NAMES "" PARENT_SCOPE)
    endif()
    list(APPEND DUCKDB_OOTE_EXTENSION_NAMES ${TARGET_NAME})
    set(DUCKDB_OOTE_EXTENSION_${TARGET_NAME}_PATH ../src)
    set(DUCKDB_OOTE_EXTENSION_${TARGET_NAME}_SHOULD_LINK TRUE)

    add_subdirectory(duckdb)

    target_link_libraries(duckdb ${TARGET_NAME}_extension)
    target_link_libraries(duckdb_static ${TARGET_NAME}_extension)
endif()