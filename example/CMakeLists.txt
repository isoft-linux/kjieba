add_executable(kjieba-query query.cpp)
target_link_libraries(kjieba-query KJieba::KJieba)

install(TARGETS kjieba-query ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
