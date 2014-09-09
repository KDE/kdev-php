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
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${php_SOURCE_DIR}/cmake/)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings)

find_package(Qt5 REQUIRED Core Widgets Test)
find_package(KF5 REQUIRED COMPONENTS KDELibs4Support ThreadWeaver TextEditor I18n)
find_package(KDevPlatform ${KDEVPLATFORM_VERSION} REQUIRED)
find_package(KDevelop-PG-Qt REQUIRED)

include_directories(${KDEVPLATFORM_INCLUDE_DIR})

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/duchain
    ${CMAKE_CURRENT_SOURCE_DIR}/parser
    ${CMAKE_CURRENT_BINARY_DIR}/parser
)

add_definitions( -DKDE_DEFAULT_DEBUG_AREA=9043 )

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

include_directories(
    ${CMAKE_BINARY_DIR}/parser
    ${KDEVPGQT_INCLUDE_DIR}
)

add_subdirectory(app_templates)
add_subdirectory(parser)
add_subdirectory(duchain)
add_subdirectory(completion)
# FIXME: After the KF5 port, the testprovider plugin compiles but fails to link.
#add_subdirectory(testprovider)

set(kdevphplanguagesupport_PART_SRCS
    phplanguagesupport.cpp
    phpparsejob.cpp
    phphighlighting.cpp

    codegen/refactoring.cpp
)

add_library(kdevphplanguagesupport MODULE ${kdevphplanguagesupport_PART_SRCS})

target_link_libraries(kdevphplanguagesupport
    ${KDEVPLATFORM_INTERFACES_LIBRARIES}
    ${KDEVPLATFORM_LANGUAGE_LIBRARIES}
    phpduchain
    phpparser
    phpcompletion

    KF5::I18n
    KF5::TextEditor

    # TODO: remove once KDevPlatform moves away from KDELibs4Support.
    KF5::KDELibs4Support
)

install(TARGETS kdevphplanguagesupport DESTINATION ${PLUGIN_INSTALL_DIR})

configure_file(kdevphpsupport.desktop.cmake ${CMAKE_CURRENT_BINARY_DIR}/kdevphpsupport.desktop)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/kdevphpsupport.desktop DESTINATION ${SERVICES_INSTALL_DIR})
# not writeable so that the refactoring actions get hidden
install(FILES phpfunctions.php DESTINATION ${DATA_INSTALL_DIR}/kdevphpsupport PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)

include(CTest)

# CTestCustom.cmake has to be in the CTEST_BINARY_DIR.
# in the KDE build system, this is the same as CMAKE_BINARY_DIR.
configure_file(${CMAKE_SOURCE_DIR}/CTestCustom.cmake ${CMAKE_BINARY_DIR}/CTestCustom.cmake)
