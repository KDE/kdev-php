set(kdevphpunitprovider_PLUGIN_SRCS
    phpunitprovider.cpp
    phpunittestsuite.cpp
    phpunitrunjob.cpp
    testdoxdelegate.cpp
)
ecm_qt_declare_logging_category(kdevphpunitprovider_PLUGIN_SRCS
    HEADER testproviderdebug.h
    IDENTIFIER TESTPROVIDER
    CATEGORY_NAME "kdevelop.languages.php.testprovider"
)

kdevplatform_add_plugin(kdevphpunitprovider
    JSON kdevphpunitprovider.json
    SOURCES ${kdevphpunitprovider_PLUGIN_SRCS}
)

target_link_libraries(kdevphpunitprovider LINK_PRIVATE
    KDev::Interfaces
    KDev::Language
    KDev::Project
    KDev::OutputView
    KDev::Util
)

install(FILES phpunitdeclarations.php DESTINATION ${KDE_INSTALL_DATADIR}/kdevphpsupport)


