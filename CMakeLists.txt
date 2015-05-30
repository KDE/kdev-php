PROJECT(php)

set(KDEVPHP_VERSION_MAJOR 1)
set(KDEVPHP_VERSION_MINOR 9)
set(KDEVPHP_VERSION_PATCH 90)
# KDevplatform dependency version
set( KDEVPLATFORM_VERSION "${KDEVPHP_VERSION_MAJOR}.${KDEVPHP_VERSION_MINOR}.${KDEVPHP_VERSION_PATCH}" )

configure_file( "${php_SOURCE_DIR}/kdevphpversion.h.cmake" "${php_BINARY_DIR}/kdevphpversion.h" @ONLY )

cmake_minimum_required(VERSION 2.8.12)
find_package (ECM 0.0.9 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH})

include(ECMAddTests)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings)

find_package(Qt5 REQUIRED Core Widgets Test)
find_package(KF5 REQUIRED COMPONENTS KDELibs4Support ThreadWeaver TextEditor I18n)
find_package(KDevPlatform ${KDEVPLATFORM_VERSION} REQUIRED)
find_package(KDevelop-PG-Qt REQUIRED)

add_definitions( -DKDE_DEFAULT_DEBUG_AREA=9043 )

include_directories(
    ${KDEVPGQT_INCLUDE_DIR}
)

add_subdirectory(app_templates)
add_subdirectory(parser)
add_subdirectory(duchain)
add_subdirectory(completion)
add_subdirectory(testprovider)

set(kdevphplanguagesupport_PART_SRCS
    phplanguagesupport.cpp
    phpparsejob.cpp
    phphighlighting.cpp
    phpdebug.cpp

    codegen/refactoring.cpp
)

add_library(kdevphplanguagesupport MODULE ${kdevphplanguagesupport_PART_SRCS})

target_link_libraries(kdevphplanguagesupport
    KDev::Interfaces
    KDev::Language
    kdevphpduchain
    kdevphpparser
    kdevphpcompletion

    KF5::I18n
    KF5::TextEditor
)

install(TARGETS kdevphplanguagesupport DESTINATION ${PLUGIN_INSTALL_DIR}/kdevplatform/${KDEV_PLUGIN_VERSION})

configure_file(kdevphpsupport.desktop.cmake ${CMAKE_CURRENT_BINARY_DIR}/kdevphpsupport.desktop)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/kdevphpsupport.desktop DESTINATION ${SERVICES_INSTALL_DIR})
# not writeable so that the refactoring actions get hidden
install(FILES phpfunctions.php DESTINATION ${DATA_INSTALL_DIR}/kdevphpsupport PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)