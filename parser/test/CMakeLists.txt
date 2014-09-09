include_directories(${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    )

set(lexertest_SRCS lexertest.cpp)
kde4_add_unit_test(lexertest ${lexertest_SRCS})

target_link_libraries(lexertest phpparser
    Qt5::Test
    Qt5::Core
    KDev::Language
)
