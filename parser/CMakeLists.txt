add_subdirectory(test)

set(parser_STAT_SRCS
    phplexer.cpp
    parsesession.cpp
    )

kdevpgqt_generate(parser_SRCS php NAMESPACE Php DEBUG_VISITOR TOKEN_TEXT
    "${php_SOURCE_DIR}/parser/php.g"
    "${php_SOURCE_DIR}/parser/phplexer.h"
)

kde4_add_library( kdev4phpparser SHARED ${parser_SRCS} ${parser_STAT_SRCS} )
target_link_libraries( kdev4phpparser
    ${KDE4_KDECORE_LIBS}
    ${KDEVPLATFORM_LANGUAGE_LIBRARIES}
    ${KDE4_KTEXTEDITOR_LIBS}
)

kde4_add_executable( php-parser main.cpp )
target_link_libraries(php-parser ${QT_QTCORE_LIBRARY} ${KDEVPLATFORM_TESTS_LIBRARIES} ${KDEVPLATFORM_LANGUAGE_LIBRARIES} kdev4phpparser)

install(TARGETS kdev4phpparser DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})
