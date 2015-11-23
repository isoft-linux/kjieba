project(kjieba)
cmake_minimum_required(VERSION 2.8.12)
set(PROJECT_VERSION "0.1.0")
set(PROJECT_SOVERSION 0)
set(LIBCPPJIEBAR_DIR ${CMAKE_INSTALL_PREFIX}/share/libcppjieba)
set(LIBCPPJIEBAR_DICT_DIR ${LIBCPPJIEBAR_DIR}/dict)

add_definitions("-DPROJECT_VERSION=\"${PROJECT_VERSION}\"")
add_definitions("-DLIBCPPJIEBAR_DIR=\"${LIBCPPJIEBAR_DIR}\"")
add_definitions("-DLIBCPPJIEBAR_DICT_DIR=\"${LIBCPPJIEBAR_DICT_DIR}\"")

add_definitions(-std=c++11)
option(ENABLE_DEBUG "Enable debug" OFF)
if(ENABLE_DEBUG)
    add_definitions(-g -DDEBUG)
endif()

find_package(ECM 1.3.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

find_package(Qt5 REQUIRED COMPONENTS Core Widgets DBus)
find_package(KF5 REQUIRED COMPONENTS I18n DBusAddons)

include(FeatureSummary)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings)
include(ECMPackageConfigHelpers)

add_subdirectory(dbus)
add_subdirectory(lib)
add_subdirectory(example)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
