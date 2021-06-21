cmake_minimum_required(VERSION 3.16)
project(kdev-php VERSION "5.6.40")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(QT_MIN_VERSION "5.15.0")
set(KF5_DEP_VERSION "5.78.0")

find_package(Threads)
find_package (ECM ${KF5_DEP_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

include(ECMAddTests)
include(ECMQtDeclareLoggingCategory)
include(GenerateExportHeader)
include(CMakePackageConfigHelpers)
include(ECMSetupVersion)
include(FeatureSummary)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED Core Widgets)

find_package(KF5 ${KF5_DEP_VERSION} REQUIRED COMPONENTS
    ThreadWeaver
    TextEditor
    I18n
    KCMUtils
)
if(BUILD_TESTING)
  find_package(Qt5Test ${QT_MIN_VERSION} CONFIG REQUIRED)
endif()
# KDevplatform dependency version
set(KDEVPLATFORM_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")
find_package(KDevPlatform ${KDEVPLATFORM_VERSION} CONFIG REQUIRED)

ecm_setup_version(
    ${PROJECT_VERSION}
    VARIABLE_PREFIX KDEVPHP
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/kdevphpversion.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KDevPHPConfigVersion.cmake"
)


set(KDEVPHP_INCLUDE_DIR ${KDE_INSTALL_INCLUDEDIR}/kdev-php)
set(KDEVPHP_PRIVATE_INCLUDE_DIR ${KDEVPHP_INCLUDE_DIR}/private/${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})

find_package(KDevelop-PG-Qt REQUIRED)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wdocumentation")
endif()

add_definitions( -DTRANSLATION_DOMAIN=\"kdevphp\" )

include_directories(
    ${KDEVPGQT_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}
)

add_subdirectory(app_templates)
add_subdirectory(parser)
add_subdirectory(duchain)
add_subdirectory(completion)
add_subdirectory(testprovider)
add_subdirectory(docs)

set(kdevphplanguagesupport_PART_SRCS
    phplanguagesupport.cpp
    phpparsejob.cpp
    phphighlighting.cpp

    codegen/refactoring.cpp
)
ecm_qt_declare_logging_category(kdevphplanguagesupport_PART_SRCS
    HEADER phpdebug.h
    IDENTIFIER PHP
    CATEGORY_NAME "kdevelop.plugins.php"
)

kdevplatform_add_plugin(kdevphplanguagesupport JSON kdevphpsupport.json
    SOURCES ${kdevphplanguagesupport_PART_SRCS})
target_link_libraries(kdevphplanguagesupport
    KDev::Interfaces
    KDev::Language
    kdevphpduchain
    kdevphpparser
    kdevphpcompletion

    KF5::I18n
    KF5::TextEditor

    Threads::Threads
)

# not writeable so that the refactoring actions get hidden
install(FILES phpfunctions.php DESTINATION ${KDE_INSTALL_DATADIR}/kdevphpsupport PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)

install(FILES org.kde.kdev-php.metainfo.xml DESTINATION ${KDE_INSTALL_METAINFODIR})

# kdebugsettings file
# kdebugsettings >= 18.12 supports/pushes for some newer, not backward-compatible format.
# For ECM >= 5.59 we install categories files to new location, which is only supported by
# newer kdebugsettings also supporting the new content format, so we use that as base.
if (ECM_VERSION VERSION_GREATER "5.58.0")
    install(FILES kdevphpsupport-newformat.categories RENAME kdevphpsupport.categories
        DESTINATION ${KDE_INSTALL_LOGGINGCATEGORIESDIR}
    )
else()
    install(FILES kdevphpsupport-oldformat.categories RENAME kdevphpsupport.categories
        DESTINATION ${KDE_INSTALL_CONFDIR}
    )
endif()

# create a Config.cmake and a ConfigVersion.cmake file and install them
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KDevPHP")

configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/KDevPHPConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/KDevPHPConfig.cmake"
  INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/KDevPHPConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/KDevPHPConfigVersion.cmake"
  DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
  COMPONENT Devel
)

install(EXPORT KDevPHPTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KDevPHPTargets.cmake)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/kdevphpversion.h" DESTINATION ${KDEVPHP_INCLUDE_DIR})

ki18n_install(po)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
