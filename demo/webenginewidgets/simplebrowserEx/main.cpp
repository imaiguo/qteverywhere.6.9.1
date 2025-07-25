
// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "browser.h"
#include "browserwindow.h"
#include "tabwidget.h"
#include <QApplication>
#include <QLoggingCategory>
#include <QWebEngineProfile>
#include <QWebEngineSettings>

using namespace Qt::StringLiterals;

const static QString LITTLEBLUEURL = "https://www.doubao.com/chat/";

int main(int argc, char **argv){
    QCoreApplication::setOrganizationName("QtExamples");

    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(u":image/AppLogoColor.png"_s));
    QLoggingCategory::setFilterRules(u"qt.webenginecontext.debug=true"_s);

    QWebEngineProfile::defaultProfile()->settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    QWebEngineProfile::defaultProfile()->settings()->setAttribute(QWebEngineSettings::DnsPrefetchEnabled, true);
    QWebEngineProfile::defaultProfile()->settings()->setAttribute(QWebEngineSettings::ScreenCaptureEnabled, true);

    Browser browser;
    BrowserWindow *window = browser.createHiddenWindow();
    window->tabWidget()->setUrl(QUrl(LITTLEBLUEURL));
    window->show();
    return app.exec();
}
