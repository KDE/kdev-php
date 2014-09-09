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

add_library( phpcompletion STATIC ${completion_SRCS} )

target_link_libraries(phpcompletion LINK_PRIVATE
    KDev::Language
    KDev::Interfaces
    KDev::Project
    phpduchain
    phpparser
 )
