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

add_library(kdevphpparser SHARED ${parser_SRCS} ${parser_STAT_SRCS})

generate_export_header(kdevphpparser EXPORT_MACRO_NAME KDEVPHPPARSER_EXPORT
                                      EXPORT_FILE_NAME parserexport.h)
target_link_libraries(kdevphpparser LINK_PRIVATE
    KDev::Language
)

add_executable(php-parser main.cpp)

# hack to make phpdebugvisitor.h (generated at compile time)
# use the correct EXPORT tags when compiling in MinGW
if (MINGW)
    add_definitions(-DMAKE_KDEV4PHPPARSER_LIB)
endif (MINGW)

target_link_libraries(php-parser
    KDev::Tests
    KDev::Language
    kdevphpparser
)

install(TARGETS kdevphpparser DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})
