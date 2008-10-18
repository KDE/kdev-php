set( EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR} )


include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${KDevPlatform_INCLUDE_DIR}
)

set(duchaintest_SRCS test_duchain.cpp)
kde4_add_unit_test(duchaintest ${duchaintest_SRCS})
target_link_libraries(duchaintest kdev4phpduchain ${QT_QTTEST_LIBRARY})


set(expressionparsertest_SRCS test_expressionparser.cpp)
kde4_add_unit_test(expressionparsertest ${expressionparsertest_SRCS})
target_link_libraries(expressionparsertest kdev4phpduchain ${QT_QTTEST_LIBRARY})

set(usestest_SRCS test_uses.cpp)
kde4_add_unit_test(usestest ${usestest_SRCS})
target_link_libraries(usestest kdev4phpduchain ${QT_QTTEST_LIBRARY})
