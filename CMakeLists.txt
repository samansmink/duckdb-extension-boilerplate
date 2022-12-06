cmake_minimum_required(VERSION 2.8.12)

# Configure extension name here
set(TARGET_NAME boilerplate)
project(${TARGET_NAME})

if(DEFINED EXTERNAL_EXTENSION_DIRECTORIES)
    # Building from DuckDB CMake
    add_subdirectory(src)
else()
    # Building duckdb within the extension
    set(EXTENSION_CLASS ${TARGET_NAME}Extension)
    string(SUBSTRING ${TARGET_NAME} 0 1 FIRST_LETTER)
    string(TOUPPER ${FIRST_LETTER} FIRST_LETTER)
    string(REGEX REPLACE "^.(.*)" "${FIRST_LETTER}\\1" EXTENSION_CLASS
            "${TARGET_NAME}")

    cmake_policy(SET CMP0079 NEW)

    include_directories(src/include)
    add_compile_definitions(DUCKDB_OUT_OF_TREE)
    add_compile_definitions(DUCKDB_EXTENSION_NAME=${TARGET_NAME})
    add_compile_definitions(DUCKDB_EXTENSION_CLASS=${EXTENSION_CLASS}Extension)
    add_compile_definitions(DUCKDB_EXTENSION_HEADER="${TARGET_NAME}_extension.hpp")

    # Todo: src here is confusing, because this will result in the build folder being called src
    set(EXTERNAL_EXTENSION_DIRECTORIES ../src)

    add_subdirectory(duckdb duckdb_library)

    target_link_libraries(duckdb ${TARGET_NAME}_extension)
    target_link_libraries(duckdb_static ${TARGET_NAME}_extension)
endif()