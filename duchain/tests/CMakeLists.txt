include_directories(${CMAKE_BINARY_DIR}/completion)
ecm_add_test(
    duchain.cpp
    duchaintestbase.cpp
    TEST_NAME duchain
    LINK_LIBRARIES
        kdevphpduchain
        kdevphpparser
        Qt5::Test
        KDev::Tests
        KDev::Language
        KF5::KDELibs4Support
)

set(expressionparser_SRCS)
ecm_add_test(
    expressionparser.cpp
    duchaintestbase.cpp
    TEST_NAME expressionparser
    LINK_LIBRARIES
        kdevphpduchain
        kdevphpparser
        Qt5::Test
        KDev::Tests
        KDev::Language
        KF5::KDELibs4Support
)

ecm_add_test(
    uses.cpp
    duchaintestbase.cpp
    TEST_NAME uses
    LINK_LIBRARIES
        kdevphpduchain
        kdevphpparser
        Qt5::Test
        KDev::Tests
        KDev::Language
        KDev::Interfaces
        KF5::KDELibs4Support
)
ecm_add_test(
    benchmarks.cpp
    duchaintestbase.cpp
    TEST_NAME benchmarks
    LINK_LIBRARIES
        kdevphpduchain
        kdevphpparser
        Qt5::Test
        KDev::Tests
        KDev::Language
        KDev::Interfaces
        KF5::KDELibs4Support
)

set(duchain_multiplefiles_SRCS
)
ecm_add_test(
    duchain_multiplefiles.cpp
    duchaintestbase.cpp
    TEST_NAME duchain_multiplefiles
    LINK_LIBRARIES
        kdevphpduchain
        kdevphpparser
        Qt5::Test
        KDev::Tests
        KDev::Language
        KDev::Interfaces
        KF5::KDELibs4Support
)

