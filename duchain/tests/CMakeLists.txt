set(duchain_SRCS
    duchain.cpp
    duchaintestbase.cpp
)

kde4_add_unit_test(duchain ${duchain_SRCS})
target_link_libraries(duchain
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


set(expressionparser_SRCS
    expressionparser.cpp
    duchaintestbase.cpp)
kde4_add_unit_test(expressionparser ${expressionparser_SRCS})
target_link_libraries(expressionparser
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


set(uses_SRCS
    uses.cpp
    duchaintestbase.cpp)
kde4_add_unit_test(uses ${uses_SRCS})
target_link_libraries(uses
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


set(benchmarks_SRCS
    benchmarks.cpp
    duchaintestbase.cpp
)
kde4_add_unit_test(benchmarks ${benchmarks_SRCS})
target_link_libraries(benchmarks
    kdev4phpduchain
    kdev4phpparser
    Qt5::Test
    KDev::Tests
    KDev::Language
    KDev::Interfaces

    # TODO: KF5: KDevice is forcing us to have this dependency. I'm sure
    # we can work-around it :)
    KF5::Archive
)
# hack to make ../duchaintestbase.h use the correct EXPORT tags when compiling with MinGW
if (MINGW)
    set_property(TARGET benchmarks APPEND_STRING PROPERTY COMPILE_FLAGS " -DMAKE_KDEV4PHPDUCHAIN_LIB")
endif (MINGW)


set(duchain_multiplefiles_SRCS
    duchain_multiplefiles.cpp
    duchaintestbase.cpp
)
kde4_add_unit_test(duchain_multiplefiles ${duchain_multiplefiles_SRCS})
target_link_libraries(duchain_multiplefiles
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
