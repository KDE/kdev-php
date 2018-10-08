ecm_add_test(
    test_completion.cpp
    ../../duchain/tests/duchaintestbase.cpp
    TEST_NAME completiontest
    LINK_LIBRARIES
        kdevphpcompletion
        kdevphpduchain
        kdevphpparser
        Qt5::Test
        KDev::Tests
        KDev::Language
)

ecm_add_test(
    bench_completion.cpp
    ../../duchain/tests/duchaintestbase.cpp
    TEST_NAME completionbenchmark
    LINK_LIBRARIES
        kdevphpcompletion
        kdevphpduchain
        kdevphpparser

        Qt5::Test
        KDev::Tests
        KDev::Language
)
