########## shared settings ##########
set(kdevphpdocs_settings_SRCS
)

kconfig_add_kcfg_files( kdevphpdocs_settings_SRCS phpdocssettings.kcfgc )

########## Documentation Plugin #####

set(kdevphpdocs_SRCS
    phpdocumentationwidget.cpp
    phpdocumentation.cpp
    phpdocsplugin.cpp
    phpdocsmodel.cpp
    ${kdevphpdocs_settings_SRCS}
)

add_library(kdevphpdocs MODULE ${kdevphpdocs_SRCS})

target_link_libraries(kdevphpdocs
    KDev::Interfaces
    KDev::Language
    KDev::Documentation
    # TODO: remove this
    KF5::KCMUtils
    KF5::KDELibs4Support
)

configure_file(kdevphpdocs.desktop.cmake ${CMAKE_CURRENT_BINARY_DIR}/kdevphpdocs.desktop)
kcoreaddons_desktop_to_json(kdevphpdocs ${CMAKE_CURRENT_BINARY_DIR}/kdevphpdocs.desktop)
install(TARGETS kdevphpdocs DESTINATION ${PLUGIN_INSTALL_DIR}/kdevplatform/${KDEV_PLUGIN_VERSION})

### Configuration module for PHP documentation plugin

set(kcm_kdevphpdocs_SRCS
    phpdocsconfig.cpp
    ${kdevphpdocs_settings_SRCS}
)

qt5_wrap_ui(kcm_kdevphpdocs_SRCS phpdocsconfig.ui)

add_library( kcm_kdevphpdocs MODULE ${kcm_kdevphpdocs_SRCS} )
target_link_libraries( kcm_kdevphpdocs
    KF5::ConfigWidgets
    KF5::KIOWidgets
    KF5::I18n
    # TODO: remove this
    KF5::KCMUtils
    KF5::KDELibs4Support
)

configure_file(kcm_kdevphpdocs.desktop.cmake ${CMAKE_CURRENT_BINARY_DIR}/kcm_kdevphpdocs.desktop)
kcoreaddons_desktop_to_json(kcm_kdevphpdocs ${CMAKE_CURRENT_BINARY_DIR}/kcm_kdevphpdocs.desktop)
install( TARGETS kcm_kdevphpdocs DESTINATION ${PLUGIN_INSTALL_DIR}/kdevplatform/${KDEV_PLUGIN_VERSION}/kcm )
install( FILES ${CMAKE_CURRENT_BINARY_DIR}/kcm_kdevphpdocs.desktop DESTINATION ${SERVICES_INSTALL_DIR} )
