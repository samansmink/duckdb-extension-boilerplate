cmake_minimum_required(VERSION 2.8.12)

# Configure extension name here
set(TARGET_NAME boilerplate)
project(${TARGET_NAME})

# This functions registers the name in the list of OOTEs and sets the required variables for duckdb to generate
# the required include and LoadExtension code
function(register_duckdb_oote NAME PATH SHOULD_LINK)
    if (NOT DEFINED DUCKDB_OOTE_EXTENSION_NAMES)
        set(DUCKDB_OOTE_EXTENSION_NAMES "" PARENT_SCOPE)
    endif()
    list(APPEND DUCKDB_OOTE_EXTENSION_NAMES ${NAME})
    set(DUCKDB_OOTE_EXTENSION_NAMES ${DUCKDB_OOTE_EXTENSION_NAMES} PARENT_SCOPE)
    set(DUCKDB_OOTE_EXTENSION_${NAME}_PATH ${PATH} PARENT_SCOPE)
    set(DUCKDB_OOTE_EXTENSION_${NAME}_SHOULD_LINK ${SHOULD_LINK} PARENT_SCOPE)
endfunction(register_duckdb_oote)

cmake_policy(SET CMP0079 NEW)

include_directories(src/include)

# Register the OOTE for DuckDB to build it.
register_duckdb_oote(${TARGET_NAME} "../src" "TRUE")

add_subdirectory(duckdb)

target_link_libraries(duckdb ${TARGET_NAME}_extension)
target_link_libraries(duckdb_static ${TARGET_NAME}_extension)