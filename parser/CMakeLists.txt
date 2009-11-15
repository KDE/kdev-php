add_subdirectory(test)

set(parser_STAT_SRCS
    phplexer.cpp
    parsesession.cpp
    )

if(KDEVPGQT_FOUND)
     kdevpgqt_generate(_kdevpgList php NAMESPACE Php DEBUG_VISITOR TOKEN_TEXT
        "${php_SOURCE_DIR}/parser/php.g"
        "${php_SOURCE_DIR}/parser/phplexer.h"
    )
    set( parser_SRCS
       ${_kdevpgList}
   )
else(KDEVPGQT_FOUND)
   message(STATUS "Assuming existence of generated parser files")
   set(parser_SRCS
       generated/phpparser.cpp
       generated/phpvisitor.cpp
       generated/phpdefaultvisitor.cpp )

endif(KDEVPGQT_FOUND)


kde4_add_library( kdev4phpparser SHARED ${parser_SRCS} ${parser_STAT_SRCS} )
target_link_libraries( kdev4phpparser
    ${KDE4_KDECORE_LIBS}
    ${KDEVPLATFORM_LANGUAGE_LIBRARIES}
    ${KDE4_KTEXTEDITOR_LIBS}
)

kde4_add_executable( php-parser main.cpp )
target_link_libraries(php-parser ${QT_QTCORE_LIBRARY} kdev4phpparser)

install(TARGETS kdev4phpparser DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})


add_custom_target( copy-generated
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${php_BINARY_DIR}/parser/phpparser.cpp" "${php_SOURCE_DIR}/parser/generated/phpparser.cpp"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${php_BINARY_DIR}/parser/phpparser.h" "${php_SOURCE_DIR}/parser/generated/phpparser.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${php_BINARY_DIR}/parser/phpast.h" "${php_SOURCE_DIR}/parser/generated/phpast.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${php_BINARY_DIR}/parser/phpvisitor.h" "${php_SOURCE_DIR}/parser/generated/phpvisitor.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${php_BINARY_DIR}/parser/phpvisitor.cpp" "${php_SOURCE_DIR}/parser/generated/phpvisitor.cpp"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${php_BINARY_DIR}/parser/phpdefaultvisitor.h" "${php_SOURCE_DIR}/parser/generated/phpdefaultvisitor.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${php_BINARY_DIR}/parser/phpdefaultvisitor.cpp" "${php_SOURCE_DIR}/parser/generated/phpdefaultvisitor.cpp"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${php_BINARY_DIR}/parser/phpdebugvisitor.h" "${php_SOURCE_DIR}/parser/generated/phpdebugvisitor.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${php_BINARY_DIR}/parser/phptokentext.h" "${php_SOURCE_DIR}/parser/generated/phptokentext.h"
    DEPENDS "${php_BINARY_DIR}/parser/phpparser.cpp"
    DEPENDS "${php_BINARY_DIR}/parser/phpparser.h"
    DEPENDS "${php_BINARY_DIR}/parser/phpvisitor.cpp"
    DEPENDS "${php_BINARY_DIR}/parser/phpvisitor.h"
    DEPENDS "${php_BINARY_DIR}/parser/phpdefaultvisitor.cpp"
    DEPENDS "${php_BINARY_DIR}/parser/phpdefaultvisitor.h"
    DEPENDS "${php_BINARY_DIR}/parser/phpast.h"
    DEPENDS "${php_BINARY_DIR}/parser/phpdebugvisitor.h"
    DEPENDS "${php_BINARY_DIR}/parser/phptokentext.h"
    )
