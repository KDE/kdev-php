PROJECT(php)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${php_SOURCE_DIR}/cmake/)
enable_testing()

#To properly find kdevelop-pg add -DKDEVPG_DATA_DIR=<kdevpg-install-path>/share to the
#cmake run if you installed it in a different directory than this plugin
#TODO: a cmake run is needed after changing one of the CMakeLists.txt, make will
#complain about the FindKDevelop-PG.cmake file not findable.
find_package(KDE4 REQUIRED)

if( extragear-sdk_SOURCE_DIR )
    if ( ${extragear-sdk_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR}  )
        set( KDEVPLATFORM_FOUND TRUE )
        include_directories( ${CMAKE_SOURCE_DIR}/kdevplatform )
        set( KDEVPLATFORM_INTERFACES_LIBRARIES kdevplatforminterfaces )
        set( KDEVPLATFORM_SHELL_LIBRARIES kdevplatformshell )
        set( KDEVPLATFORM_TESTS_LIBRARIES kdevplatformtests )
        set( KDEVPLATFORM_UTIL_LIBRARIES kdevplatformutil )
        set( KDEVPLATFORM_PROJECT_LIBRARIES kdevplatformproject )
        set( KDEVPLATFORM_OUTPUTVIEW_LIBRARIES kdevplatformoutputview )
        set( KDEVPLATFORM_LANGUAGE_LIBRARIES kdevplatformlanguage )
        set( KDEVPLATFORM_VCS_LIBRARIES kdevplatformvcs )
        set( KDEVPLATFORM_DEBUGGER_LIBRARIES kdevplatformdebugger )
        set( KDEVPLATFORM_SUBLIME_LIBRARIES sublime )
        include( ${CMAKE_SOURCE_DIR}/kdevplatform/cmake/modules/KDevPlatformMacros.cmake )
    endif ( ${extragear-sdk_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR}  )
endif( extragear-sdk_SOURCE_DIR )

if( NOT KDEVPLATFORM_FOUND )

    find_package(KDevPlatform 0.9.97 REQUIRED)
    include_directories(${KDEVPLATFORM_INCLUDE_DIR})

endif( NOT KDEVPLATFORM_FOUND )

include_directories(
    ${KDE4_INCLUDES}
    ${KDE4_INCLUDE_DIR}/threadweaver
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/duchain
    ${CMAKE_CURRENT_SOURCE_DIR}/parser
    ${CMAKE_CURRENT_BINARY_DIR}/parser
)

add_definitions( -DKDE_DEFAULT_DEBUG_AREA=9043 )

#Don't error out if the FindXXX are missing for these two
find_package(KDevelop-PG-Qt QUIET)

if(KDEVPGQT_FOUND)
    include_directories(
        ${CMAKE_BINARY_DIR}/parser
        ${KDEVPGQT_INCLUDE_DIR}
    )
else(KDEVPGQT_FOUND)
    include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/parser/generated
        ${CMAKE_CURRENT_SOURCE_DIR}/parser/generated/kdevelop-pg-qt
    )
endif(KDEVPGQT_FOUND)

add_subdirectory(app_templates)
add_subdirectory(parser)
add_subdirectory(duchain)
add_subdirectory(completion)

set(kdevphplanguagesupport_PART_SRCS
    phplanguagesupport.cpp
    phpparsejob.cpp
    phphighlighting.cpp
)

kde4_add_plugin(kdevphplanguagesupport ${kdevphplanguagesupport_PART_SRCS})

target_link_libraries(kdevphplanguagesupport
    ${KDE4_KDEUI_LIBS}
    ${KDEVPLATFORM_INTERFACES_LIBRARIES}
    ${KDEVPLATFORM_LANGUAGE_LIBRARIES}
    ${KDE4_THREADWEAVER_LIBRARIES}
    ${KDE4_KTEXTEDITOR_LIBS}
    kdev4phpduchain
    kdev4phpparser
    kdev4phpcompletion
)

install(TARGETS kdevphplanguagesupport DESTINATION ${PLUGIN_INSTALL_DIR})

install(FILES kdevphpsupport.desktop DESTINATION ${SERVICES_INSTALL_DIR})
install(FILES phpfunctions.php.gz DESTINATION ${DATA_INSTALL_DIR}/kdevphpsupport)
