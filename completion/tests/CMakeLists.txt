set( EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR} )


include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${KDEVPLATFORM_INCLUDE_DIR}
)

set(completiontest_SRCS test_completion.cpp)
kde4_add_unit_test(completiontest ${completiontest_SRCS})
target_link_libraries(completiontest kdev4phpcompletion kdev4phpduchain ${QT_QTTEST_LIBRARY})

set(completionbench_SRCS bench_completion.cpp)
kde4_add_unit_test(completionbenchmark ${completionbench_SRCS})
target_link_libraries(completionbenchmark kdev4phpcompletion kdev4phpduchain ${QT_QTTEST_LIBRARY})