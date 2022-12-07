#define DUCKDB_EXTENSION_MAIN

#include "boilerplate_extension.hpp"
#include "duckdb.hpp"

#include <duckdb/parser/parsed_data/create_scalar_function_info.hpp>

namespace duckdb {

inline void BoilerPlateScalarFun(DataChunk &args, ExpressionState &state, Vector &result) {
    result.Reference(Value("I'm a boilerplate!"));
}

static void LoadInternal(DatabaseInstance &instance) {
	Connection con(instance);
    con.BeginTransaction();

    auto &catalog = Catalog::GetCatalog(*con.context);

    CreateScalarFunctionInfo boilerplatify_info(
            ScalarFunction("do_a_boilerplate", {}, LogicalType::VARCHAR, BoilerPlateScalarFun));
    boilerplatify_info.on_conflict = OnCreateConflict::ALTER_ON_CONFLICT;
    catalog.CreateFunction(*con.context, &boilerplatify_info);
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
