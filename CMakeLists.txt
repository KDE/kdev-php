PROJECT(phpdocs)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${phpdocs_SOURCE_DIR}/cmake/)
enable_testing()

find_package(KDE4 REQUIRED)
find_package(KDevPlatform REQUIRED)
include_directories(${KDEVPLATFORM_INCLUDE_DIR})

include_directories(
    ${KDE4_INCLUDES}
    ${KDE4_INCLUDE_DIR}/threadweaver
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_definitions( -DKDE_DEFAULT_DEBUG_AREA=9043 )

########## shared settings ##########
set(kdevphpdocs_settings_SRCS
)

kde4_add_kcfg_files(kdevphpdocs_settings_SRCS phpdocssettings.kcfgc)

install(FILES phpdocssettings.kcfg DESTINATION ${KCFG_INSTALL_DIR})

########## Documentation Plugin #####

set(kdevphpdocs_SRCS
    phpdocumentationwidget.cpp
    phpdocumentation.cpp
    phpdocsplugin.cpp
    phpdocsmodel.cpp
    ${kdevphpdocs_settings_SRCS}
)

kde4_add_plugin(kdevphpdocs ${kdevphpdocs_SRCS})

target_link_libraries(kdevphpdocs
    ${KDE4_KDEUI_LIBS} ${KDE4_KTEXTEDITOR_LIBS} ${KDE4_KHTML_LIBS} ${KDE4_KUTILS_LIBS}
    ${KDEVPLATFORM_INTERFACES_LIBRARIES} ${KDEVPLATFORM_LANGUAGE_LIBRARIES}
)

install(TARGETS kdevphpdocs DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES kdevphpdocs.desktop DESTINATION ${SERVICES_INSTALL_DIR})


### Configuration module for PHP documentation plugin

set(kdevphpdocs_config_SRCS
    phpdocsconfig.cpp
    ${kdevphpdocs_settings_SRCS}
)

set(kdevphpdocs_config_UI
    phpdocsconfig.ui
)

kde4_add_ui_files(kdevphpdocs_config_SRCS ${kdevphpdocs_config_UI})

kde4_add_plugin( kdevphpdocs_config ${kdevphpdocs_config_SRCS} )

target_link_libraries( kdevphpdocs_config ${KDE4_KUTILS_LIBS} ${KDE4_KIO_LIBS} )

install( TARGETS kdevphpdocs_config DESTINATION ${PLUGIN_INSTALL_DIR} )
install( FILES kdevphpdocs_config.desktop DESTINATION ${SERVICES_INSTALL_DIR} )
