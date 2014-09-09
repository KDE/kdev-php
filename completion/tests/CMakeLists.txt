set( EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR} )

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
)

set(completiontest_SRCS test_completion.cpp
    ../../duchain/tests/duchaintestbase.cpp)
kde4_add_unit_test(completiontest ${completiontest_SRCS})
target_link_libraries(completiontest
    phpcompletion
    phpduchain
    phpparser
    Qt5::Test
    KDev::Tests
    KDev::Language
)

set(completionbench_SRCS bench_completion.cpp
    ../../duchain/tests/duchaintestbase.cpp)
kde4_add_unit_test(completionbenchmark ${completionbench_SRCS})
target_link_libraries(completionbenchmark
    phpcompletion
    phpduchain
    phpparser

    Qt5::Test
    KDev::Tests
    KDev::Language

    # TODO: KF5: KDevice is forcing us to have this dependency. I'm sure
    # we can work-around it :)
    KF5::Archive
)