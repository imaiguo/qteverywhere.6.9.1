# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

cmake_minimum_required(VERSION 3.16)
project(hello LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(QT_NO_PRIVATE_MODULE_WARNING ON)

# 静态库配置
# set(CMAKE_PREFIX_PATH "D:/devtools/Qt.6.9.1/static/lib/cmake;D:/devtools/openssl.3.0.8;")

# 动态库配置
set(CMAKE_PREFIX_PATH "D:/devtools/Qt.6.9.1/lib/cmake;D:/devtools/openssl.3.0.8;")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(hello
    WIN32
    MACOSX_BUNDLE
    main.cpp
)

target_link_libraries(hello PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
)

qt_add_qml_module(hello
    URI ImageModel
    QML_FILES qml/main.qml
    NO_RESOURCE_TARGET_PATH
)

install(TARGETS hello
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_qml_app_script(
    TARGET hello
    OUTPUT_SCRIPT deploy_script
    MACOS_BUNDLE_POST_BUILD
    NO_UNSUPPORTED_PLATFORM_ERROR
    DEPLOY_USER_QML_MODULES_ON_UNSUPPORTED_PLATFORM
)

install(SCRIPT ${deploy_script})
