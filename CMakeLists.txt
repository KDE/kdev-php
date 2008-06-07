PROJECT(php)


#To properly find kdevelop-pg add -DKDEVPG_DATA_DIR=<kdevpg-install-path>/share to the
#cmake run if you installed it in a different directory than this plugin
#TODO: a cmake run is needed after changing one of the CMakeLists.txt, make will
#complain about the FindKDevelop-PG.cmake file not findable.
find_package(KDE4 REQUIRED)

find_package(KDevPlatform REQUIRED)

include_directories(
    ${KDEVPLATFORM_INCLUDE_DIR}
    ${KDE4_INCLUDES}
    ${KDE4_INCLUDE_DIR}/threadweaver
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/duchain
    ${CMAKE_SOURCE_DIR}/parser
)

#add_definitions( -DKDE_DEFAULT_DEBUG_AREA=9011 )

#Don't error out if the FindXXX are missing for these two
find_package(KDevelop-PG-Qt QUIET)

if(KDEVPGQT_FOUND)
    include_directories(
        ${CMAKE_BINARY_DIR}/parser
        ${KDEVPGQT_INCLUDE_DIR}
    )
else(KDEVPGQT_FOUND)
    include_directories(
        ${CMAKE_SOURCE_DIR}/parser/generated
        ${CMAKE_SOURCE_DIR}/parser/generated/kdevelop-pg-qt
    )
endif(KDEVPGQT_FOUND)


add_subdirectory(parser)

