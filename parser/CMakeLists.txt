include_directories(${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    )

set(parser_STAT_SRCS
    phplexer.cpp
    parsesession.cpp
     )

if(KDEVPGQT_FOUND)
     kdevpgqt_generate(_kdevpgList php NAMESPACE Php DEBUG_VISITOR
        "${CMAKE_SOURCE_DIR}/parser/php.g"
        "${CMAKE_SOURCE_DIR}/parser/phplexer.h"
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
target_link_libraries( kdev4phpparser ${KDE4_KDECORE_LIBS} )

kde4_add_executable( php-parser main.cpp )
target_link_libraries(php-parser ${QT_QTCORE_LIBRARY} kdev4phpparser)

install(TARGETS php-parser ${INSTALL_TARGETS_DEFAULT_ARGS})
install(TARGETS kdev4phpparser DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})


add_custom_target( copy-generated
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_BINARY_DIR}/parser/phpparser.cpp" "${CMAKE_SOURCE_DIR}/parser/generated/phpparser.cpp"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_BINARY_DIR}/parser/phpparser.h" "${CMAKE_SOURCE_DIR}/parser/generated/phpparser.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_BINARY_DIR}/parser/phpast.h" "${CMAKE_SOURCE_DIR}/parser/generated/phpast.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_BINARY_DIR}/parser/phpvisitor.h" "${CMAKE_SOURCE_DIR}/parser/generated/phpvisitor.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_BINARY_DIR}/parser/phpvisitor.cpp" "${CMAKE_SOURCE_DIR}/parser/generated/phpvisitor.cpp"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_BINARY_DIR}/parser/phpdefaultvisitor.h" "${CMAKE_SOURCE_DIR}/parser/generated/phpdefaultvisitor.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_BINARY_DIR}/parser/phpdefaultvisitor.cpp" "${CMAKE_SOURCE_DIR}/parser/generated/phpdefaultvisitor.cpp"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_BINARY_DIR}/parser/phpdebugvisitor.h" "${CMAKE_SOURCE_DIR}/parser/generated/phpdebugvisitor.h"
    DEPENDS "${CMAKE_BINARY_DIR}/parser/phpparser.cpp"
    DEPENDS "${CMAKE_BINARY_DIR}/parser/phpparser.h"
    DEPENDS "${CMAKE_BINARY_DIR}/parser/phpvisitor.cpp"
    DEPENDS "${CMAKE_BINARY_DIR}/parser/phpvisitor.h"
    DEPENDS "${CMAKE_BINARY_DIR}/parser/phpdefaultvisitor.cpp"
    DEPENDS "${CMAKE_BINARY_DIR}/parser/phpdefaultvisitor.h"
    DEPENDS "${CMAKE_BINARY_DIR}/parser/phpast.h"
    DEPENDS "${CMAKE_BINARY_DIR}/parser/phpdebugvisitor.h"
    )
