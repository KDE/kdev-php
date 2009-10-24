add_subdirectory(tests)

include_directories(${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    )

set(duchain_SRCS
    integraltypeextended.cpp
    structuretype.cpp
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
    variabledeclaration.cpp
    classmethoddeclaration.cpp
    classdeclaration.cpp
    functiondeclaration.cpp
    tests/duchaintestbase.cpp
    navigation/navigationwidget.cpp
    navigation/declarationnavigationcontext.cpp
    navigation/includenavigationcontext.cpp
    navigation/magicconstantnavigationcontext.cpp
    )


kde4_add_library( kdev4phpduchain SHARED ${duchain_SRCS} )
target_link_libraries(kdev4phpduchain
    ${KDE4_KDECORE_LIBS}
    ${KDE4_KTEXTEDITOR_LIBS}
    ${KDEVPLATFORM_INTERFACES_LIBRARIES}
    ${KDEVPLATFORM_LANGUAGE_LIBRARIES}
    ${KDEVPLATFORM_SHELL_LIBRARIES}
    ${KDEVPLATFORM_PROJECT_LIBRARIES}
    kdev4phpparser
 )

install(TARGETS kdev4phpduchain DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})

