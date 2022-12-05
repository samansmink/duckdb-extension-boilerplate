#define DUCKDB_EXTENSION_MAIN

#include "boilerplate_extension.hpp"

#include "duckdb.hpp"
#ifndef DUCKDB_AMALGAMATION
#include "duckdb/common/arrow/result_arrow_wrapper.hpp"
#include "duckdb/common/arrow/arrow_appender.hpp"
#include "duckdb/common/arrow/arrow_converter.hpp"
#include "duckdb/parser/parsed_data/create_table_function_info.hpp"
#include "duckdb/function/table/arrow.hpp"
#endif

namespace duckdb {

inline int32_t hello_fun(string_t what) {
    return what.GetSize() + 5;
}

void BoilerPlateExtension::Load(DuckDB &db) {
	auto instance = *db.instance;
    Connection con(instance);
    con.BeginTransaction();
    con.CreateScalarFunction<int32_t, string_t>("hello", {LogicalType(LogicalTypeId::VARCHAR)},
                                                LogicalType(LogicalTypeId::INTEGER), &hello_fun);
    catalog.CreateFunction(client_context, &hello_alias_info);

    con.Commit();
}
std::string BoilerPlateExtension::Name() {
	return "boilerplate";
}

} // namespace duckdb

extern "C" {

DUCKDB_EXTENSION_API void boilerplate_init(duckdb::DatabaseInstance &db) {
	LoadInternal(db);
}

DUCKDB_EXTENSION_API const char *boilerplate_version() {
	return duckdb::DuckDB::LibraryVersion();
}
}

#ifndef DUCKDB_EXTENSION_MAIN
#error DUCKDB_EXTENSION_MAIN not defined
#endif
