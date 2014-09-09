set(duchain_SRCS
    duchain.cpp
    duchaintestbase.cpp
)

kde4_add_unit_test(duchain ${duchain_SRCS})
target_link_libraries(duchain
    phpduchain
    phpparser
    Qt5::Test
    KDev::Tests
    KDev::Language
)

set(expressionparser_SRCS
    expressionparser.cpp
    duchaintestbase.cpp)
kde4_add_unit_test(expressionparser ${expressionparser_SRCS})
target_link_libraries(expressionparser
    phpduchain
    phpparser
    Qt5::Test
    KDev::Tests
    KDev::Language
)

set(uses_SRCS
    uses.cpp
    duchaintestbase.cpp)
kde4_add_unit_test(uses ${uses_SRCS})
target_link_libraries(uses
    phpduchain
    phpparser
    Qt5::Test
    KDev::Tests
    KDev::Language
    KDev::Interfaces
)

set(benchmarks_SRCS
    benchmarks.cpp
    duchaintestbase.cpp
)
kde4_add_unit_test(benchmarks ${benchmarks_SRCS})
target_link_libraries(benchmarks
    phpduchain
    phpparser
    Qt5::Test
    KDev::Tests
    KDev::Language
    KDev::Interfaces

    # TODO: KF5: KDevice is forcing us to have this dependency. I'm sure
    # we can work-around it :)
    KF5::Archive
)

set(duchain_multiplefiles_SRCS
    duchain_multiplefiles.cpp
    duchaintestbase.cpp
)
kde4_add_unit_test(duchain_multiplefiles ${duchain_multiplefiles_SRCS})
target_link_libraries(duchain_multiplefiles
    phpduchain
    phpparser
    Qt5::Test
    KDev::Tests
    KDev::Language
    KDev::Interfaces
)
