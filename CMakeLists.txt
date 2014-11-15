PROJECT(phpdocs)

set(KDEVPHPDOCS_VERSION_MAJOR 1)
set(KDEVPHPDOCS_VERSION_MINOR 9)
set(KDEVPHPDOCS_VERSION_PATCH 90)
# KDevplatform dependency version
set( KDEVPLATFORM_VERSION "${KDEVPHPDOCS_VERSION_MAJOR}.${KDEVPHPDOCS_VERSION_MINOR}.${KDEVPHPDOCS_VERSION_PATCH}" )

configure_file( "${phpdocs_SOURCE_DIR}/kdevphpdocsversion.h.cmake" "${phpdocs_BINARY_DIR}/kdevphpdocsversion.h" @ONLY )

cmake_minimum_required(VERSION 2.8.12)
find_package (ECM 0.0.9 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH})

include(ECMAddTests)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings)

find_package(Qt5 REQUIRED Core Widgets Test WebKitWidgets)
find_package(KF5 REQUIRED COMPONENTS KDELibs4Support ConfigWidgets KIO I18n KCMUtils TextEditor ThreadWeaver )
find_package(KDevPlatform ${KDEVPLATFORM_VERSION} REQUIRED)

add_definitions( -DKDE_DEFAULT_DEBUG_AREA=9043 )

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

include(CTest)

# CTestCustom.cmake has to be in the CTEST_BINARY_DIR.
# in the KDE build system, this is the same as CMAKE_BINARY_DIR.
configure_file(${CMAKE_SOURCE_DIR}/CTestCustom.cmake ${CMAKE_BINARY_DIR}/CTestCustom.cmake)
