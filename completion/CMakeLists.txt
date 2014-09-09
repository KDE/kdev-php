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

target_link_libraries(kdev4phpcompletion LINK_PRIVATE
    KDev::Language
    KDev::Interfaces
    KDev::Project
    kdev4phpduchain
    kdev4phpparser
)

install(TARGETS kdev4phpcompletion DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})

# hack to make ../parser/phpdebugvisitor.h (generated at compile time)
# use the correct EXPORT tags when compiling in MinGW
if (MINGW)
    add_definitions(-DMAKE_KDEV4PHPPARSER_LIB)
endif (MINGW)
