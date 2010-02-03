set( EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR} )


include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${KDEVPLATFORM_INCLUDE_DIR}
)

set(duchain_SRCS duchain.cpp)
kde4_add_unit_test(duchain ${duchain_SRCS})
target_link_libraries(duchain kdev4phpduchain ${QT_QTTEST_LIBRARY})


set(expressionparser_SRCS expressionparser.cpp)
kde4_add_unit_test(expressionparser ${expressionparser_SRCS})
target_link_libraries(expressionparser kdev4phpduchain ${QT_QTTEST_LIBRARY})

set(uses_SRCS uses.cpp)
kde4_add_unit_test(uses ${uses_SRCS})
target_link_libraries(uses
    kdev4phpduchain
    ${QT_QTTEST_LIBRARY}
    ${KDEVPLATFORM_INTERFACES_LIBRARIES}
)

set(benchmarks_SRCS
    benchmarks.cpp
)
kde4_add_unit_test(benchmarks ${benchmarks_SRCS})
target_link_libraries(benchmarks
    kdev4phpduchain
    ${QT_QTTEST_LIBRARY}
    ${KDEVPLATFORM_INTERFACES_LIBRARIES}
)
