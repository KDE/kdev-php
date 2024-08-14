cmake_minimum_required(VERSION 3.16)

# KDE Gear version, managed by release service script
set(RELEASE_SERVICE_VERSION_MAJOR "24")
set(RELEASE_SERVICE_VERSION_MINOR "11")
set(RELEASE_SERVICE_VERSION_MICRO "70")

# generate patch level from release service version
set(_micro ${RELEASE_SERVICE_VERSION_MICRO})
if (_micro LESS "10")
    string(PREPEND _micro "0") # pad with 0
endif()
set(RELEASE_SERVICE_BASED_PATCHLEVEL "${RELEASE_SERVICE_VERSION_MAJOR}${RELEASE_SERVICE_VERSION_MINOR}${_micro}")

project(kdev-php VERSION "6.0.${RELEASE_SERVICE_BASED_PATCHLEVEL}")

set(KDE_COMPILERSETTINGS_LEVEL 6.0)
set(QT_MIN_VERSION "6.5.0")
set(KF_MIN_VERSION "6.0.0")

find_package(Threads)
find_package (ECM ${KF_MIN_VERSION} REQUIRED)
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

find_package(Qt6 ${QT_MIN_VERSION} REQUIRED COMPONENTS
    Core
    Widgets
)

find_package(KF6 ${KF_MIN_VERSION} REQUIRED COMPONENTS
    ThreadWeaver
    TextEditor
    I18n
    KCMUtils
)
if(BUILD_TESTING)
  find_package(Qt6Test ${QT_MIN_VERSION} REQUIRED)
endif()

# KDevplatform dependency version
set(KDEVPLATFORM_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")
find_package(KDevPlatform ${KDEVPLATFORM_VERSION} REQUIRED)

ecm_setup_version(
    ${PROJECT_VERSION}
    VARIABLE_PREFIX KDEVPHP
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/kdevphpversion.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KDevPHPConfigVersion.cmake"
)

set(KDEVPHP_INCLUDE_DIR ${KDE_INSTALL_INCLUDEDIR}/kdev-php)
set(KDEVPHP_PRIVATE_INCLUDE_DIR ${KDEVPHP_INCLUDE_DIR}/private/${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})

find_package(KDevelop-PG-Qt 2.3 REQUIRED)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wdocumentation")
endif()

add_definitions( -DTRANSLATION_DOMAIN=\"kdevphp\" )

# TODO: we also need to fix kdevelop-pg-qt before we can remove these
remove_definitions(
    -DQT_NO_FOREACH
    -DQT_NO_KEYWORDS
    -DQT_NO_CAST_FROM_ASCII
    -DQT_NO_CAST_FROM_BYTEARRAY
    -DQT_NO_CAST_TO_ASCII
)

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
    DESCRIPTION "KDevelop plugin: PHP language support"
    EXPORT KDEVPHP
)

kdevplatform_add_plugin(kdevphplanguagesupport JSON kdevphpsupport.json
    SOURCES ${kdevphplanguagesupport_PART_SRCS})
target_link_libraries(kdevphplanguagesupport
    KDev::Interfaces
    KDev::Language
    kdevphpduchain
    kdevphpparser
    kdevphpcompletion

    KF6::I18n
    KF6::TextEditor

    Threads::Threads
)

# not writeable so that the refactoring actions get hidden
install(FILES phpfunctions.php DESTINATION ${KDE_INSTALL_DATADIR}/kdevphpsupport PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)

install(FILES org.kde.kdev-php.metainfo.xml DESTINATION ${KDE_INSTALL_METAINFODIR})

# kdebugsettings file
ecm_qt_install_logging_categories(
    EXPORT KDEVPHP
    FILE kdevphpsupport.categories
    DESTINATION ${KDE_INSTALL_LOGGINGCATEGORIESDIR}
)

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
