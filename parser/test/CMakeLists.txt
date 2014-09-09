include_directories(${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    )

set(lexertest_SRCS lexertest.cpp)
kde4_add_unit_test(lexertest ${lexertest_SRCS})

target_link_libraries(lexertest phpparser ${QT_QTTEST_LIBRARY} ${QT_QTCORE_LIBRARY} ${KDE4_KDECORE_LIBS} ${KDEVPLATFORM_LANGUAGE_LIBRARIES})
