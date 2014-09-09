set(lexertest_SRCS lexertest.cpp)
kde4_add_unit_test(lexertest ${lexertest_SRCS})

target_link_libraries(lexertest
    kdev4phpparser
    Qt5::Test
    Qt5::Core
    KDev::Language
)

# hack to make ../phpdebugvisitor.h (generated at compile time)
# use the correct EXPORT tags when compiling in MinGW
if (MINGW)
    add_definitions(-DMAKE_KDEV4PHPPARSER_LIB)
endif (MINGW)
