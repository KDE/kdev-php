include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_subdirectory(tests)

set(duchain_SRCS
    types/integraltypeextended.cpp
    types/structuretype.cpp
    builders/predeclarationbuilder.cpp
    builders/declarationbuilder.cpp
    builders/contextbuilder.cpp
    builders/usebuilder.cpp
    builders/typebuilder.cpp
    editorintegrator.cpp
    dumptypes.cpp
    expressionvisitor.cpp
    expressionparser.cpp
    expressionevaluationresult.cpp
    helper.cpp
    phpducontext.cpp
    declarations/variabledeclaration.cpp
    declarations/classmethoddeclaration.cpp
    declarations/classdeclaration.cpp
    declarations/functiondeclaration.cpp
    declarations/namespacedeclaration.cpp
    declarations/namespacealiasdeclaration.cpp
    declarations/traitmethodaliasdeclaration.cpp
    declarations/traitmemberaliasdeclaration.cpp
    navigation/navigationwidget.cpp
    navigation/declarationnavigationcontext.cpp
    navigation/includenavigationcontext.cpp
    navigation/magicconstantnavigationcontext.cpp
    completioncodemodel.cpp
    duchaindebug.cpp
)

add_library( kdev4phpduchain SHARED ${duchain_SRCS} )

generate_export_header(kdev4phpduchain EXPORT_MACRO_NAME KDEVPHPDUCHAIN_EXPORT
                                       EXPORT_FILE_NAME phpduchainexport.h)

target_link_libraries(kdev4phpduchain LINK_PRIVATE
    KDev::Interfaces
    KDev::Language
    KDev::Shell
    KDev::Project
    KF5::KDELibs4Support
    kdev4phpparser
)

install(TARGETS kdev4phpduchain DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})

