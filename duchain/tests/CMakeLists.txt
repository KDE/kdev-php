set( EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR} )

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${KDEVPLATFORM_INCLUDE_DIR}
)

set(duchain_SRCS
    duchain.cpp
    duchaintestbase.cpp)
kde4_add_unit_test(duchain ${duchain_SRCS})
target_link_libraries(duchain
    phpduchain
    phpparser
    ${QT_QTTEST_LIBRARY}
    ${KDEVPLATFORM_TESTS_LIBRARIES}
    ${KDEVPLATFORM_LANGUAGE_LIBRARIES}
)

set(expressionparser_SRCS
    expressionparser.cpp
    duchaintestbase.cpp)
kde4_add_unit_test(expressionparser ${expressionparser_SRCS})
target_link_libraries(expressionparser
    phpduchain
    phpparser
    ${QT_QTTEST_LIBRARY}
    ${KDEVPLATFORM_TESTS_LIBRARIES}
    ${KDEVPLATFORM_LANGUAGE_LIBRARIES}
)

set(uses_SRCS
    uses.cpp
    duchaintestbase.cpp)
kde4_add_unit_test(uses ${uses_SRCS})
target_link_libraries(uses
    phpduchain
    phpparser
    ${QT_QTTEST_LIBRARY}
    ${KDEVPLATFORM_INTERFACES_LIBRARIES}
    ${KDEVPLATFORM_TESTS_LIBRARIES}
    ${KDEVPLATFORM_LANGUAGE_LIBRARIES}
)

set(benchmarks_SRCS
    benchmarks.cpp
    duchaintestbase.cpp
)
kde4_add_unit_test(benchmarks ${benchmarks_SRCS})
target_link_libraries(benchmarks
    phpduchain
    phpparser
    ${QT_QTTEST_LIBRARY}
    ${KDEVPLATFORM_INTERFACES_LIBRARIES}
    ${KDEVPLATFORM_TESTS_LIBRARIES}
    ${KDEVPLATFORM_LANGUAGE_LIBRARIES}

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
    ${QT_QTTEST_LIBRARY}
    ${KDEVPLATFORM_INTERFACES_LIBRARIES}
    ${KDEVPLATFORM_TESTS_LIBRARIES}
    ${KDEVPLATFORM_LANGUAGE_LIBRARIES}
)
