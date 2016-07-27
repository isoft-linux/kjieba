add_library(krunner_kjieba MODULE kjiebarunner.cpp)
target_link_libraries(krunner_kjieba 
    KJieba::KJieba
    KF5::Runner
    KF5::I18n
    KF5::Service
    KF5::Activities
    KF5::KIOWidgets
)

install(TARGETS krunner_kjieba DESTINATION ${KDE_INSTALL_PLUGINDIR})

install(FILES plasma-runner-kjieba.desktop DESTINATION ${KDE_INSTALL_KSERVICES5DIR})
