add_subdirectory(tests)

include_directories(${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    )

set(duchain_SRCS
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
    tests/duchaintestbase.cpp
    navigation/navigationwidget.cpp
    navigation/declarationnavigationcontext.cpp
    )


kde4_add_library( kdev4phpduchain SHARED ${duchain_SRCS} )
target_link_libraries(kdev4phpduchain
    ${KDE4_KDECORE_LIBS}
    ${KDevPlatform_LANGUAGE_LIBRARY}
    ${KDE4_KTEXTEDITOR_LIBS}
    ${KDevPlatform_INTERFACES_LIBRARY}
    kdev4phpparser
 )

install(TARGETS kdev4phpduchain DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})

