# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(cloxcTests LANGUAGES C)

# ---- Tests ----

add_executable(cloxc_test source/cloxc_test.c)
target_link_libraries(cloxc_test PRIVATE cloxc_lib)
target_compile_features(cloxc_test PRIVATE c_std_11)

add_test(NAME cloxc_test COMMAND cloxc_test)

# ---- End-of-file commands ----

add_folders(Test)
