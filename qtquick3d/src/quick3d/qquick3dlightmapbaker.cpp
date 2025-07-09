// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "qquick3dlightmapbaker_p.h"
#include "qquick3dviewport_p.h"

QT_BEGIN_NAMESPACE

QQuick3DLightmapBaker::QQuick3DLightmapBaker(QQuick3DViewport *view) :
    QObject(view), m_bakingControl(new BakingControl()), m_view(view)
{

}

QQuick3DLightmapBaker::~QQuick3DLightmapBaker()
{
    if (m_lmWindow) {
        m_lmWindow->close();
        delete m_lmWindow;
    }

    delete m_bakingControl;
}

/*!
    Triggers a new frame where lightmap baking will take place.
    Will call \a callback for feedback and handling.

    \note Lightmap baking is a slow blocking operation running on the
    render thread. The application will be frozen until completed.
*/
void QQuick3DLightmapBaker::bake(Callback callback)
{
    Q_ASSERT(m_view);
    m_bakingRequested = true;
    m_bakingControl->reset();
    m_callback = callback;
    updateView();
}

/*!
    \internal
*/
void QQuick3DLightmapBaker::bake()
{
    Q_ASSERT(m_view);
    if (m_currentlyBaking)
        return;
    m_bakingRequested = true;
    m_bakingControl->reset();

    m_windowCancelRequested = false;

    if (!m_lmWindow) {
        m_lmWindow = new QQuickView();
        m_lmWindow->setSource(QUrl::fromLocalFile(QStringLiteral(":/qt-project.org/imports/QtQuick3D/Helpers/impl/LightmapperOutputWindow.qml")));
        m_lmWindow->show();
        m_lmWindow->setProperty("width", 400);
        m_lmWindow->setProperty("height", 400);

        QObject *rootObject = m_lmWindow->rootObject();
        QObject *cancelButton = rootObject->findChild<QObject *>(QStringLiteral("cancelButton"));
        if (cancelButton)
            QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(onLmCancelButtonClicked()));

        QObject::connect(m_lmWindow, &QQuickWindow::closing, this, &QQuick3DLightmapBaker::onLmWindowClosing);
    } else {
        QObject *rootObject = m_lmWindow->rootObject();
        QMetaObject::invokeMethod(rootObject, "clearText");
    }

    m_callback = [this] (
            BakingStatus status,
            std::optional<QString> msg,
            BakingControl *bakingControl) {
        if (m_windowCancelRequested && !bakingControl->isCancelled())
            bakingControl->requestCancel();

        QQuickWindow *window = m_view->window();
        if (status == BakingStatus::Complete) {
            QMetaObject::invokeMethod(window, "releaseResources", Qt::QueuedConnection);
            updateView();
            m_currentlyBaking = false;
            QQuickWindowPrivate::get(window)->updatesEnabled = true;
        } else if (status != BakingStatus::None) {
            if (status == BakingStatus::Progress)
                QQuickWindowPrivate::get(window)->updatesEnabled = false;
            else if (status == BakingStatus::Cancelled) {
                QQuickWindowPrivate::get(window)->updatesEnabled = true;
                m_currentlyBaking = false;
            }

            if (m_lmWindow && msg.has_value()) {
                QString result = msg.value();
                if (status == BakingStatus::Warning)
                    result.prepend(QStringLiteral("Warning: "));
                else if (status == BakingStatus::Error)
                    result.prepend(QStringLiteral("Error: "));

                QObject *rootObject = m_lmWindow->rootObject();
                QMetaObject::invokeMethod(rootObject,
                                          "appendText",
                                          Q_ARG(QString, result));
            }
        }
    };

    m_currentlyBaking = true;
    updateView();
}

void QQuick3DLightmapBaker::updateView()
{
    QMetaObject::invokeMethod(m_view, "update", Qt::QueuedConnection);
}

void QQuick3DLightmapBaker::onLmCancelButtonClicked()
{
    if (m_windowCancelRequested)
        return;

    m_windowCancelRequested = true;
}

void QQuick3DLightmapBaker::onLmWindowClosing(QQuickCloseEvent *event)
{
    Q_UNUSED(event);

    onLmCancelButtonClicked();
    m_lmWindow->deleteLater();
    m_lmWindow = nullptr;
}

void QQuick3DLightmapBaker::BakingControl::reset() {
    cancelFlag = false;
}

void QQuick3DLightmapBaker::BakingControl::requestCancel() {
    cancelFlag = true;
}

bool QQuick3DLightmapBaker::BakingControl::isCancelled() const {
    return cancelFlag;
}

QT_END_NAMESPACE
