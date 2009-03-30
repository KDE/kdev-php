add_subdirectory(tests)

include_directories(${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    )

set(duchain_SRCS
    includebuilder.cpp
    predeclarationbuilder.cpp
    declarationbuilder.cpp
    contextbuilder.cpp
    editorintegrator.cpp
    usebuilder.cpp
    typebuilder.cpp
    dumptypes.cpp
    expressionvisitor.cpp
    expressionparser.cpp
    expressionevaluationresult.cpp
    helper.cpp
    phpducontext.cpp
    constantdeclaration.cpp
    variabledeclaration.cpp
    classmethoddeclaration.cpp
    tests/duchaintestbase.cpp
    navigation/navigationwidget.cpp
    navigation/declarationnavigationcontext.cpp
    )


kde4_add_library( kdev4phpduchain SHARED ${duchain_SRCS} )
target_link_libraries(kdev4phpduchain
    ${KDE4_KDECORE_LIBS}
    ${KDE4_KTEXTEDITOR_LIBS}
    ${KDEVPLATFORM_INTERFACES_LIBRARY}
    ${KDEVPLATFORM_LANGUAGE_LIBRARY}
    ${KDEVPLATFORM_SHELL_LIBRARY}
    ${KDEVPLATFORM_PROJECT_LIBRARY}
    kdev4phpparser
 )

install(TARGETS kdev4phpduchain DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})

