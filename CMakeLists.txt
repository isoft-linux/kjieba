project(kjieba)

cmake_minimum_required(VERSION 2.8.12)

# ECM setup
find_package(ECM 5.24.0  NO_MODULE)
include(FeatureSummary)
set_package_properties(ECM PROPERTIES TYPE REQUIRED DESCRIPTION "Extra CMake Modules." URL "https://projects.kde.org/projects/kdesupport/extra-cmake-modules")

set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

set(PROJECT_VERSION "0.5.0")
set(PROJECT_SOVERSION 0)
set(LIBCPPJIEBAR_DIR ${CMAKE_INSTALL_PREFIX}/share/libcppjieba)
set(LIBCPPJIEBAR_DICT_DIR ${LIBCPPJIEBAR_DIR}/dict)

add_definitions("-DPROJECT_VERSION=\"${PROJECT_VERSION}\"")
add_definitions("-DLIBCPPJIEBAR_DIR=\"${LIBCPPJIEBAR_DIR}\"")
add_definitions("-DLIBCPPJIEBAR_DICT_DIR=\"${LIBCPPJIEBAR_DICT_DIR}\"")

add_definitions(-std=c++14)
option(ENABLE_DEBUG "Enable debug" OFF)
if(ENABLE_DEBUG)
    add_definitions(-g -DDEBUG)
endif()

find_package(Qt5 REQUIRED COMPONENTS Core Widgets DBus)
find_package(KF5 REQUIRED COMPONENTS I18n DBusAddons Runner Service Activities KIO)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings)
include(ECMPackageConfigHelpers)

add_subdirectory(dbus)
add_subdirectory(lib)
add_subdirectory(krunner)
add_subdirectory(example)
add_subdirectory(po)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
