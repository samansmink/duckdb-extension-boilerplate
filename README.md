Disclaimer: this repo is work-in-progress, follow https://github.com/duckdb and https://duckdb.org/news/ for the official launch.

# DuckDB Extension  boilerplate
This repository forms the base for the github template to build your own DuckDB extension. The main goal of this template is to allow users to easily create and build their own DuckDB extension.

## Build
To build the extension:
```sh
make release
```
The main things that will be built are:
```sh
./build/release/duckdb/duckdb
./build/release/duckdb/test/unittest
./build/release/duckdb/extension/<extension_name>/<extension_name>.duckdb_extension
```
- `duckdb` is the binary for the duckdb shell with the extension code automatically loaded. 
- `unittest` is the test runner of duckdb. Again, the extension is already linked into the binary.
- `<extension_name>.duckdb_extension` is the loadable binary as it would be distributed.

## Running the extension
To run the extension code, simply start the shell with `./build/release/duckdb/duckdb`.

Now we can use the features from the extension directly in DuckDB:
```
D select do_a_boilerplate() as result;
┌────────────────────┐
│       result       │
│      varchar       │
├────────────────────┤
│ I'm a boilerplate! │
└────────────────────┘
```

## Running the tests
Different tests can be created for DuckDB extensions. Most important are probably the SQL tests. These tests can be run using:
```sh
make test_release
```

## Getting started with your own extension
After creating a repository from this template, the first step is to name your extension. To rename the extension, run:
```
./scripts/set_extension_name.sh <extension_name_you_want>
```
Feel free to delete the script after this step.

Now you're good to go! After a (re)build, you should now be able to use your duckdb extension:
```
./build/release/duckdb/duckdb
D select do_a_<extension_name_you_chose>() as result;
┌───────────────────────────────────┐
│                result             │
│               varchar             │
├───────────────────────────────────┤
│ I'm a <extension_name_you_chose>! │
└───────────────────────────────────┘
```

## Distributing your extension
Note 