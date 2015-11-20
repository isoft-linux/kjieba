project(klibcppjieba)
cmake_minimum_required(VERSION 2.8.12)
set(PROJECT_VERSION "0.1.0")

add_definitions(-std=c++11 -Werror)
add_definitions("-DPROJECT_VERSION=\"${PROJECT_VERSION}\"")

option(ENABLE_DEBUG "Enable debug" OFF)
if(ENABLE_DEBUG)
    add_definitions(-g -DDEBUG)
endif()

find_package(ECM 1.3.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

find_package(Qt5 REQUIRED COMPONENTS Core)
find_package(KF5 REQUIRED COMPONENTS I18n DBusAddons)

include(FeatureSummary)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings)

#add_subdirectory(dbus)
add_subdirectory(libcppjieba)
add_subdirectory(po)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
