ecm_add_test(
    test_completion.cpp
    ../../duchain/tests/duchaintestbase.cpp
    TEST_NAME completiontest
    LINK_LIBRARIES
        kdev4phpcompletion
        kdev4phpduchain
        kdev4phpparser
        Qt5::Test
        KDev::Tests
        KDev::Language
)

# hack to make ../../duchain/tests/duchaintestbase.h use the correct EXPORT tags when compiling with MinGW
if (MINGW)
    set_property(TARGET completiontest APPEND_STRING PROPERTY COMPILE_FLAGS " -DMAKE_KDEV4PHPDUCHAIN_LIB")
endif (MINGW)

ecm_add_test(
    bench_completion.cpp
    ../../duchain/tests/duchaintestbase.cpp
    TEST_NAME completionbenchmark
    LINK_LIBRARIES
        kdev4phpcompletion
        kdev4phpduchain
        kdev4phpparser

        Qt5::Test
        KDev::Tests
        KDev::Language

        # TODO: KF5: KDevice is forcing us to have this dependency. I'm sure
        # we can work-around it :)
        KF5::Archive
)

# hack to make ../../duchain/tests/duchaintestbase.h use the correct EXPORT tags when compiling with MinGW
if (MINGW)
    set_property(TARGET completionbenchmark APPEND_STRING PROPERTY COMPILE_FLAGS " -DMAKE_KDEV4PHPDUCHAIN_LIB")
endif (MINGW)
