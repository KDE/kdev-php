if (BUILD_TESTING)
    add_subdirectory(test)
endif()

set(parser_STAT_SRCS
    phplexer.cpp
    parsesession.cpp
)

kdevpgqt_generate(parser_SRCS php NAMESPACE Php DEBUG_VISITOR TOKEN_TEXT
    "${CMAKE_CURRENT_SOURCE_DIR}/php.g"
    "${CMAKE_CURRENT_SOURCE_DIR}/phplexer.h"
)
ecm_qt_declare_logging_category(parser_SRCS
    HEADER parserdebug.h
    IDENTIFIER PARSER
    CATEGORY_NAME "kdevelop.plugins.php.parser"
    DESCRIPTION "KDevelop plugin: PHP language support - parser"
    EXPORT KDEVPHP
)

add_library(kdevphpparser SHARED ${parser_SRCS} ${parser_STAT_SRCS})

generate_export_header(kdevphpparser EXPORT_MACRO_NAME KDEVPHPPARSER_EXPORT
                                      EXPORT_FILE_NAME parserexport.h)
target_link_libraries(kdevphpparser LINK_PRIVATE
    KDev::Language
    KF6::I18n
)

# hack to make phpdebugvisitor.h (generated at compile time)
# use the correct EXPORT tags when compiling in MinGW
if (MINGW)
    add_definitions(-DMAKE_KDEV4PHPPARSER_LIB)
endif (MINGW)

target_include_directories(kdevphpparser
    PUBLIC $<INSTALL_INTERFACE:${KDEVPHP_PRIVATE_INCLUDE_DIR}/parser>
    PUBLIC $<INSTALL_INTERFACE:${KDEVPHP_PRIVATE_INCLUDE_DIR}>
    PUBLIC $<INSTALL_INTERFACE:${KDEVPHP_INCLUDE_DIR}>
)

if (BUILD_TESTING)
    add_executable(php-parser main.cpp)
    target_link_libraries(php-parser
        KDev::Tests
        KDev::Language
        kdevphpparser
    )
endif()

install(TARGETS kdevphpparser EXPORT KDevPHPTargets DESTINATION ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
install(FILES
    parsesession.h
    phplexer.h
    tokenstream.h
    DESTINATION ${KDEVPHP_INCLUDE_DIR}/parser
    COMPONENT Devel
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/parserexport.h
    ${CMAKE_CURRENT_BINARY_DIR}/phpast-fwd.h
    ${CMAKE_CURRENT_BINARY_DIR}/phpast.h
    ${CMAKE_CURRENT_BINARY_DIR}/phpdebugvisitor.h
    ${CMAKE_CURRENT_BINARY_DIR}/phpdefaultvisitor.h
    ${CMAKE_CURRENT_BINARY_DIR}/phpparser.h
    ${CMAKE_CURRENT_BINARY_DIR}/phptokentext.h
    ${CMAKE_CURRENT_BINARY_DIR}/phptokentype.h
    ${CMAKE_CURRENT_BINARY_DIR}/phpvisitor.h
    DESTINATION ${KDEVPHP_PRIVATE_INCLUDE_DIR}/parser
    COMPONENT Devel
)
