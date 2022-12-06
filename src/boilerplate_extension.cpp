#define DUCKDB_EXTENSION_MAIN

#include "boilerplate_extension.hpp"

#include "duckdb.hpp"

namespace duckdb {

inline int32_t hello_fun(string_t what) {
    return what.GetSize() + 5;
}

static void LoadInternal(DatabaseInstance &instance) {
	Connection con(instance);
    con.BeginTransaction();
    con.CreateScalarFunction<int32_t, string_t>("hello", {LogicalType(LogicalTypeId::VARCHAR)},
                                                LogicalType(LogicalTypeId::INTEGER), &hello_fun);
    con.Commit();
}

void BoilerplateExtension::Load(DuckDB &db) {
	LoadInternal(*db.instance);
}
std::string BoilerplateExtension::Name() {
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
