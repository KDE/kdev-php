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
ecm_qt_declare_logging_category(kdevphpdocs_SRCS
    HEADER phpdocsdebug.h
    IDENTIFIER DOCS
    CATEGORY_NAME "kdevelop.plugins.php.docs"
    DESCRIPTION "KDevelop plugin: PHP language support - documentation"
    EXPORT KDEVPHP
)

kdevplatform_add_plugin(kdevphpdocs JSON kdevphpdocs.json
    SOURCES ${kdevphpdocs_SRCS})
target_link_libraries(kdevphpdocs
    KDev::Interfaces
    KDev::Language
    KDev::Documentation
    KF5::KCMUtils
)

### Configuration module for PHP documentation plugin

set(kcm_kdevphpdocs_SRCS
    phpdocsconfig.cpp
    ${kdevphpdocs_settings_SRCS}
)

ki18n_wrap_ui(kcm_kdevphpdocs_SRCS phpdocsconfig.ui)

add_library( kcm_kdevphpdocs MODULE ${kcm_kdevphpdocs_SRCS} )
target_link_libraries( kcm_kdevphpdocs
    KF5::ConfigWidgets
    KF5::KIOWidgets
    KF5::I18n
    KF5::KCMUtils
)

configure_file(kcm_kdevphpdocs.desktop.cmake ${CMAKE_CURRENT_BINARY_DIR}/kcm_kdevphpdocs.desktop)
kcoreaddons_desktop_to_json(kcm_kdevphpdocs ${CMAKE_CURRENT_BINARY_DIR}/kcm_kdevphpdocs.desktop)
install(TARGETS kcm_kdevphpdocs DESTINATION ${KDE_INSTALL_PLUGINDIR}/kdevplatform/${KDEV_PLUGIN_VERSION}/kcm)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/kcm_kdevphpdocs.desktop DESTINATION ${KDE_INSTALL_KSERVICES5DIR})
