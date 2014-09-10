ecm_add_test(
    duchain.cpp
    duchaintestbase.cpp
    TEST_NAME duchain
    LINK_LIBRARIES
        kdev4phpduchain
        kdev4phpparser
        Qt5::Test
        KDev::Tests
        KDev::Language
)

# hack to make ../duchaintestbase.h use the correct EXPORT tags when compiling with MinGW
if (MINGW)
    set_property(TARGET duchain APPEND_STRING PROPERTY COMPILE_FLAGS " -DMAKE_KDEV4PHPDUCHAIN_LIB")
endif (MINGW)

set(expressionparser_SRCS)
ecm_add_test(
    expressionparser.cpp
    duchaintestbase.cpp
    TEST_NAME expressionparser
    LINK_LIBRARIES
        kdev4phpduchain
        kdev4phpparser
        Qt5::Test
        KDev::Tests
        KDev::Language
)

# hack to make ../duchaintestbase.h use the correct EXPORT tags when compiling with MinGW
if (MINGW)
    set_property(TARGET expressionparser APPEND_STRING PROPERTY COMPILE_FLAGS " -DMAKE_KDEV4PHPDUCHAIN_LIB")
endif (MINGW)

ecm_add_test(
    uses.cpp
    duchaintestbase.cpp
    TEST_NAME uses
    LINK_LIBRARIES
        kdev4phpduchain
        kdev4phpparser
        Qt5::Test
        KDev::Tests
        KDev::Language
        KDev::Interfaces
)
# hack to make ../duchaintestbase.h use the correct EXPORT tags when compiling with MinGW
if (MINGW)
    set_property(TARGET uses APPEND_STRING PROPERTY COMPILE_FLAGS " -DMAKE_KDEV4PHPDUCHAIN_LIB")
endif (MINGW)

ecm_add_test(
    benchmarks.cpp
    duchaintestbase.cpp
    TEST_NAME benchmarks
    LINK_LIBRARIES
        kdev4phpduchain
        kdev4phpparser
        Qt5::Test
        KDev::Tests
        KDev::Language
        KDev::Interfaces
)

# hack to make ../duchaintestbase.h use the correct EXPORT tags when compiling with MinGW
if (MINGW)
    set_property(TARGET benchmarks APPEND_STRING PROPERTY COMPILE_FLAGS " -DMAKE_KDEV4PHPDUCHAIN_LIB")
endif (MINGW)

set(duchain_multiplefiles_SRCS
)
ecm_add_test(
    duchain_multiplefiles.cpp
    duchaintestbase.cpp
    TEST_NAME duchain_multiplefiles
    LINK_LIBRARIES
        kdev4phpduchain
        kdev4phpparser
        Qt5::Test
        KDev::Tests
        KDev::Language
        KDev::Interfaces
)

# hack to make ../duchaintestbase.h use the correct EXPORT tags when compiling with MinGW
if (MINGW)
    set_property(TARGET duchain_multiplefiles APPEND_STRING PROPERTY COMPILE_FLAGS " -DMAKE_KDEV4PHPDUCHAIN_LIB")
endif (MINGW)
