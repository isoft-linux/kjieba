include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../libcppjieba
)

set(kjieba_SRCS
    main.cpp
    daemon.cpp
)

set(kjieba_dbusAppXML org.isoftlinux.kjieba.App.xml)
qt5_add_dbus_adaptor(kjieba_SRCS ${kjieba_dbusAppXML} daemon.h Daemon)
configure_file(org.isoftlinux.kjieba.service.in
               ${CMAKE_CURRENT_BINARY_DIR}/org.isoftlinux.kjieba.service)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/org.isoftlinux.kjieba.service
        DESTINATION ${KDE_INSTALL_DBUSSERVICEDIR})

add_executable(kjieba ${kjieba_SRCS})

target_link_libraries(kjieba
    Qt5::Widgets
    KF5::I18n
    KF5::DBusAddons
)

install(TARGETS kjieba ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
install(FILES ${kjieba_dbusAppXML} DESTINATION ${KDE_INSTALL_DBUSINTERFACEDIR} )
install(FILES kjieba.desktop DESTINATION ${KDE_INSTALL_AUTOSTARTDIR})

set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KJiebaAppDBusInterface")
ecm_configure_package_config_file(KJiebaAppDBusInterfaceConfig.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/KJiebaAppDBusInterfaceConfig.cmake"
    INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/KJiebaAppDBusInterfaceConfig.cmake
    DESTINATION ${CMAKECONFIG_INSTALL_DIR})
