cmake_minimum_required(VERSION 3.20)

add_executable(nrp_test_memory test_memory.cpp)
target_link_libraries(nrp_test_memory PRIVATE nrp_core)
add_test(NAME MemoryTest COMMAND nrp_test_memory)

add_executable(nrp_test_runtime test_runtime.cpp)
target_link_libraries(nrp_test_runtime PRIVATE nrp_core)
add_test(NAME RuntimeTest COMMAND nrp_test_runtime)

add_executable(nrp_test_modules test_modules.cpp)
target_link_libraries(nrp_test_modules PRIVATE nrp_core)
add_test(NAME ModulesTest COMMAND nrp_test_modules)

add_executable(nrp_test_luau test_luau.cpp)
target_link_libraries(nrp_test_luau PRIVATE nrp_core)
add_test(NAME LuauTest COMMAND nrp_test_luau)

add_executable(nrp_test_e2e test_e2e_integration.cpp)
target_link_libraries(nrp_test_e2e PRIVATE nrp_core)
add_test(NAME E2ETest COMMAND nrp_test_e2e)

add_executable(nrp_test_full_specs test_full_specs.cpp)
target_link_libraries(nrp_test_full_specs PRIVATE nrp_core)
add_test(NAME FullSpecsTest COMMAND nrp_test_full_specs)

add_executable(nrp_test_compiler test_compiler.cpp)
target_link_libraries(nrp_test_compiler PRIVATE nrpc_lib nrp_core)
add_test(NAME CompilerTest COMMAND nrp_test_compiler)

add_executable(nrp_test_benchmark test_benchmark.cpp)
target_link_libraries(nrp_test_benchmark PRIVATE nrp_core)
add_test(NAME BenchmarkTest COMMAND nrp_test_benchmark)
