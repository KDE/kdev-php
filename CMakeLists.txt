PROJECT(phpdocs)

enable_testing()

find_package(KDE4 REQUIRED)

find_package(KDevPlatform REQUIRED)
include_directories(
    ${KDEVPLATFORM_INCLUDE_DIR}
    ${KDE4_INCLUDES}
    ${KDE4_INCLUDE_DIR}/threadweaver
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/duchain
)

cmake_minimum_required(VERSION 2.6)

add_definitions( -DKDE_DEFAULT_DEBUG_AREA=9043 )

set(kdevphpdocs_SRCS
    phpdocumentation.cpp
    phpdocsplugin.cpp
)

kde4_add_plugin(kdevphpdocs ${kdevphpdocs_SRCS})
target_link_libraries(kdevphpdocs ${KDE4_KDEUI_LIBS} ${KDE4_KTEXTEDITOR_LIBS} ${KDE4_KHTML_LIBS}
                      kdevplatformlanguage kdevplatforminterfaces)

install(TARGETS kdevphpdocs DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES kdevphpdocs.desktop DESTINATION ${SERVICES_INSTALL_DIR})
