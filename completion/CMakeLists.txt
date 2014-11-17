add_subdirectory(tests)

set(completion_SRCS
    worker.cpp
    item.cpp
    implementationitem.cpp
    includefileitem.cpp
    keyworditem.cpp
    context.cpp
    model.cpp
    helpers.cpp
    codemodelitem.cpp
    completiondebug.cpp
)

add_library( kdev4phpcompletion SHARED ${completion_SRCS} )
generate_export_header( kdev4phpcompletion EXPORT_MACRO_NAME KDEVPHPCOMPLETION_EXPORT
                                           EXPORT_FILE_NAME phpcompletionexport.h)

target_link_libraries(kdev4phpcompletion LINK_PRIVATE
    KDev::Language
    KDev::Interfaces
    KDev::Project
    kdev4phpduchain
    kdev4phpparser
    KF5::KDELibs4Support
)

install(TARGETS kdev4phpcompletion DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})
