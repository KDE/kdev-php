add_subdirectory(tests)

include_directories(${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    )

set(completion_SRCS
    worker.cpp
    item.cpp
    implementationitem.cpp
    includefileitem.cpp
    keyworditem.cpp
    context.cpp
    model.cpp
    helpers.cpp
)



kde4_add_library( kdev4phpcompletion SHARED ${completion_SRCS} )
target_link_libraries(kdev4phpcompletion
    ${KDE4_KDECORE_LIBS}
    ${KDEVPLATFORM_LANGUAGE_LIBRARY}
    ${KDE4_KTEXTEDITOR_LIBS}
    ${KDEVPLATFORM_INTERFACES_LIBRARY}
    ${KDEVPLATFORM_PROJECT_LIBRARY}
    ${KDE4_KIO_LIBS}
    kdev4phpduchain
    kdev4phpparser
 )

install(TARGETS kdev4phpcompletion DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})

