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
    types.cpp
    dumptypes.cpp
    )


kde4_add_library( kdev4phpduchain SHARED ${duchain_SRCS} )
target_link_libraries(kdev4phpduchain
    ${KDE4_KDECORE_LIBS}
    ${KDEVPLATFORM_LANGUAGE_LIBRARY}
    ${KDE4_KTEXTEDITOR_LIBS}
    ${KDEVPLATFORM_INTERFACES_LIBRARY}
    kdev4phpparser
 )

install(TARGETS kdev4phpduchain DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})

