
# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

cmake_minimum_required(VERSION 3.16)
project(simplebrowser LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui WebEngineWidgets)

qt_add_executable(simplebrowser
    main.cpp
    simplebrowser.qrc
    ./src/browser.cpp ./src/browser.h
    ./src/browserwindow.cpp ./src/browserwindow.h
    ./src/certificateerrordialog.ui
    ./src/downloadmanagerwidget.cpp ./src/downloadmanagerwidget.h ./src/downloadmanagerwidget.ui
    ./src/downloadwidget.cpp ./src/downloadwidget.h ./src/downloadwidget.ui
    ./src/passworddialog.ui
    ./src/tabwidget.cpp ./src/tabwidget.h
    ./src/webpage.cpp ./src/webpage.h
    ./src/webpopupwindow.cpp ./src/webpopupwindow.h
    ./src/webview.cpp ./src/webview.h
    ./src/webauthdialog.cpp ./src/webauthdialog.h ./src/webauthdialog.ui
)

include_directories(./src)

set_target_properties(simplebrowser PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
    MACOSX_BUNDLE_GUI_IDENTIFIER "io.qt.examples.webenginewidgets.simplebrowser"
)

target_link_libraries(simplebrowser PUBLIC
    Qt::Core
    Qt::Gui
    Qt::WebEngineWidgets
)
