set(kdevphpdocs_SRCS
    phpdocumentationwidget.cpp
    phpdocumentation.cpp
    phpdocsplugin.cpp
    phpdocsmodel.cpp
    phpdocsconfig.cpp
)
ecm_qt_declare_logging_category(kdevphpdocs_SRCS
    HEADER phpdocsdebug.h
    IDENTIFIER DOCS
    CATEGORY_NAME "kdevelop.plugins.php.docs"
    DESCRIPTION "KDevelop plugin: PHP language support - documentation"
    EXPORT KDEVPHP
)

kconfig_add_kcfg_files(kdevphpdocs_SRCS phpdocssettings.kcfgc )

ki18n_wrap_ui(kdevphpdocs_SRCS phpdocsconfig.ui)

kdevplatform_add_plugin(kdevphpdocs JSON kdevphpdocs.json
    SOURCES ${kdevphpdocs_SRCS})
target_link_libraries(kdevphpdocs
    KDev::Interfaces
    KDev::Language
    KDev::Documentation
    KF6::KIOWidgets
)
