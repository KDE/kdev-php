set(lexertest_SRCS lexertest.cpp)
kde4_add_unit_test(lexertest ${lexertest_SRCS})

target_link_libraries(lexertest phpparser
    Qt5::Test
    Qt5::Core
    KDev::Language
)
