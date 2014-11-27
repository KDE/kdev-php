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

add_library( kdevphpcompletion SHARED ${completion_SRCS} )
generate_export_header( kdevphpcompletion EXPORT_MACRO_NAME KDEVPHPCOMPLETION_EXPORT
                                           EXPORT_FILE_NAME phpcompletionexport.h)

target_link_libraries(kdevphpcompletion LINK_PRIVATE
    KDev::Language
    KDev::Interfaces
    KDev::Project
    kdevphpduchain
    kdevphpparser
    KF5::KDELibs4Support
)

install(TARGETS kdevphpcompletion DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})
