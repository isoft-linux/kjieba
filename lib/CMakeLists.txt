include(GenerateExportHeader)
include(ECMPackageConfigHelpers)
include(ECMSetupVersion)
include(ECMGenerateHeaders)

ecm_setup_version(${PROJECT_VERSION} VARIABLE_PREFIX KJIEBA
                  VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/kjieba_version.h"
                  PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KJiebaConfigVersion.cmake"
                  SOVERSION ${PROJECT_SOVERSION})

include_directories(
    ${CMAKE_SOURCE_DIR}/headers
    ${CMAKE_BINARY_DIR}/headers
)

set(SOURCES
    kjieba_interface.cpp
)

set(HEADERS
    kjieba_interface.h
)

qt5_add_dbus_interface(SOURCES
                       ${CMAKE_CURRENT_SOURCE_DIR}/../dbus/org.isoftlinux.kjieba.App.xml
                       app_interface)

add_library(KJieba SHARED ${SOURCES})
generate_export_header(KJieba EXPORT_FILE_NAME kjieba/kjieba_export.h)
add_library(KJieba::KJieba ALIAS KJieba)

target_link_libraries(KJieba
                      Qt5::Core
                      Qt5::DBus
                      Qt5::Gui
)

set(KJIEBA_INCLUDEDIR "${CMAKE_INSTALL_INCLUDEDIR}/KJieba")

target_include_directories(KJieba INTERFACE "$<INSTALL_INTERFACE:${KJIEBA_INCLUDEDIR}>")

set_target_properties(KJieba PROPERTIES
                          VERSION      ${PROJECT_VERSION}
                          SOVERSION    ${PROJECT_SOVERSION}
                          EXPORT_NAME  KJieba
)

ecm_generate_headers(KJieba_CamelCase_HEADERS
  HEADER_NAMES
    KJieba_Interface
  PREFIX
    KJieba
  REQUIRED_HEADERS KJieba_HEADERS
)
install(FILES ${KJieba_CamelCase_HEADERS}
        DESTINATION ${KJIEBA_INCLUDEDIR}/KJieba
        COMPONENT Devel)

install(TARGETS KJieba EXPORT KJiebaTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

install(
    FILES
      ${CMAKE_CURRENT_BINARY_DIR}/kjieba/kjieba_export.h
      ${KJieba_HEADERS}
      kjieba_interface.h
    DESTINATION
      ${KJIEBA_INCLUDEDIR}/kjieba
    COMPONENT
      Devel
)

# Create a Config.cmake and a ConfigVersion.cmake file and install them
set(CMAKECONFIG_INSTALL_DIR "${CMAKECONFIG_INSTALL_PREFIX}/KJieba")

ecm_configure_package_config_file("${CMAKE_CURRENT_SOURCE_DIR}/KJiebaConfig.cmake.in"
                                  "${CMAKE_CURRENT_BINARY_DIR}/KJiebaConfig.cmake"
                                  INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
                                  )

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/KJiebaConfig.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/KJiebaConfigVersion.cmake"
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel)

install(EXPORT KJiebaTargets
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        FILE KJiebaTargets.cmake NAMESPACE KJieba::)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/kjieba_version.h
        DESTINATION ${KJIEBA_INCLUDEDIR}/kjieba COMPONENT Devel)
