add_subdirectory(test)

set(parser_STAT_SRCS
    phplexer.cpp
    parsesession.cpp
    parserdebug.cpp
)

kdevpgqt_generate(parser_SRCS php NAMESPACE Php DEBUG_VISITOR TOKEN_TEXT
    "${php_SOURCE_DIR}/parser/php.g"
    "${php_SOURCE_DIR}/parser/phplexer.h"
)

add_library( phpparser STATIC ${parser_SRCS} ${parser_STAT_SRCS} )

target_link_libraries( phpparser LINK_PRIVATE
    KDev::Language
)

add_executable( php-parser main.cpp )

target_link_libraries(php-parser
    KDev::Tests
    KDev::Language
    phpparser
)
