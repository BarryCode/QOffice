////////////////////////////////////////////////////////////////////////////////
//
// QOffice - The office framework for Qt
// Copyright (C) 2016-2018 Nicolas Kogler
//
// This file is part of the Widget module.
//
// QOffice is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// QOffice is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with QOffice. If not, see <http://www.gnu.org/licenses/>.
//
////////////////////////////////////////////////////////////////////////////////

#include <QOffice/Design/OfficeAccent.hpp>
#include <QOffice/Design/OfficeImage.hpp>
#include <QOffice/Design/OfficePalette.hpp>
#include <QOffice/Widgets/Dialogs/OfficeWindow.hpp>

#include <QLayout>
#include <QPainter>
#include <QtEvents>

OffAnonymous(OfficeWindow* g_activeWindow = nullptr)
OffAnonymous(QOFFICE_CONSTEXPR int c_titleHeight = 28)

OffAnonymous(QOFFICE_CONSTEXPR OfficeWindow::ResizeDirection c_topLeft = OfficeWindow::ResizeTop | OfficeWindow::ResizeLeft)
OffAnonymous(QOFFICE_CONSTEXPR OfficeWindow::ResizeDirection c_topRight = OfficeWindow::ResizeTop | OfficeWindow::ResizeRight)
OffAnonymous(QOFFICE_CONSTEXPR OfficeWindow::ResizeDirection c_bottomLeft = OfficeWindow::ResizeBottom | OfficeWindow::ResizeLeft)
OffAnonymous(QOFFICE_CONSTEXPR OfficeWindow::ResizeDirection c_bottomRight = OfficeWindow::ResizeBottom | OfficeWindow::ResizeRight)
OffAnonymous(QOFFICE_CONSTEXPR OfficeWindow::ResizeDirection c_top = OfficeWindow::ResizeTop)
OffAnonymous(QOFFICE_CONSTEXPR OfficeWindow::ResizeDirection c_left = OfficeWindow::ResizeLeft)
OffAnonymous(QOFFICE_CONSTEXPR OfficeWindow::ResizeDirection c_bottom = OfficeWindow::ResizeBottom)
OffAnonymous(QOFFICE_CONSTEXPR OfficeWindow::ResizeDirection c_right = OfficeWindow::ResizeRight)

OfficeWindow::OfficeWindow(QWidget* parent)
    : QWidget(parent)
    , m_resizeTopLeft(new priv::ResizeArea(this, c_topLeft))
    , m_resizeTopRight(new priv::ResizeArea(this, c_topRight))
    , m_resizeBottomLeft(new priv::ResizeArea(this, c_bottomLeft))
    , m_resizeBottomRight(new priv::ResizeArea(this, c_bottomRight))
    , m_resizeTop(new priv::ResizeArea(this, c_top))
    , m_resizeLeft(new priv::ResizeArea(this, c_left))
    , m_resizeBottom(new priv::ResizeArea(this, c_bottom))
    , m_resizeRight(new priv::ResizeArea(this, c_right))
    , m_titleBar(new priv::Titlebar(this))
    , m_stateWindow(StateNone)
    , m_flagsWindow(NoFlag)
    , m_tooltipVisible(false)
{
    setGeometry(x(), y(), 600, 400);
    setFocusPolicy(Qt::ClickFocus);
    setMouseTracking(true);

    // Create a frameless window with a translucent background for the shadow.
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
    setAttribute(Qt::WA_TranslucentBackground);
}

bool OfficeWindow::hasCloseButton() const
{
    return OffHasNotFlag(m_flagsWindow, NoCloseButton);
}

bool OfficeWindow::hasMaximizeButton() const
{
    return OffHasNotFlag(m_flagsWindow, NoMaximizeButton);
}

bool OfficeWindow::hasMinimizeButton() const
{
    return OffHasNotFlag(m_flagsWindow, NoMinimizeButton);
}

bool OfficeWindow::canResize() const
{
    return OffHasNotFlag(m_flagsWindow, NoResize);
}

OfficeWindow::Flags OfficeWindow::flags() const
{
    return m_flagsWindow;
}

OfficeWindowMenu* OfficeWindow::labelMenu() const
{
    return m_titleBar->m_windowLabelMenu;
}

OfficeWindowMenu* OfficeWindow::quickMenu() const
{
    return m_titleBar->m_windowQuickMenu;
}

void OfficeWindow::setAccent(Office::Accent accent)
{
    if (OfficeAccent::isValid(accent))
    {
        const auto matches = findChildren<QWidget*>();
        for (auto* widget : matches)
        {
            // Why dynamic_cast? The problem we are facing here may look like
            // a design problem, but it is not. Imagine OfficeWidget deviring
            // from QWidget - we would never need a dynamic cast here, since we
            // could simply assume that every child is an OfficeWidget, right?
            // No, because the user might need other widgets from the Qt library
            // for which there are no office equivalents - the entire code
            // breaks because static_cast or alike would return a nullptr.
            // Also, if we devire OfficeWidget from QWidget, there is no
            // possibility of adapting the functionality of great Qt widgets
            // like QListView. Reimplementing that takes a huge amount of time!
            auto* officeWidget = dynamic_cast<OfficeWidget*>(widget);
            if (officeWidget != nullptr)
            {
                officeWidget->setAccent(accent);
            }
        }

        OfficeWidget::setAccent(accent);
    }
}

void OfficeWindow::setCloseButtonVisible(bool visible)
{
    if (visible)
    {
        OffRemoveFlag(m_flagsWindow, NoCloseButton);
    }
    else
    {
        OffAddFlag(m_flagsWindow, NoCloseButton);
    }
}

void OfficeWindow::setMaximizeButtonVisible(bool visible)
{
    if (visible)
    {
        OffRemoveFlag(m_flagsWindow, NoMaximizeButton);
    }
    else
    {
        OffAddFlag(m_flagsWindow, NoMaximizeButton);
    }
}

void OfficeWindow::setMinimizeButtonVisible(bool visible)
{
    if (visible)
    {
        OffRemoveFlag(m_flagsWindow, NoMinimizeButton);
    }
    else
    {
        OffAddFlag(m_flagsWindow, NoMinimizeButton);
    }
}

void OfficeWindow::setResizable(bool resizable)
{
    if (resizable)
    {
        OffRemoveFlag(m_flagsWindow, NoResize);
    }
    else
    {
        OffAddFlag(m_flagsWindow, NoResize);
    }
}

void OfficeWindow::setFlags(Flags flags)
{
    m_flagsWindow = flags;
}

OfficeWindow* OfficeWindow::activeWindow()
{
    return g_activeWindow;
}

void OfficeWindow::accentUpdateEvent()
{
    update();
}

void OfficeWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    // Retrieves various standardized QOffice colors.
    const QColor& colorBackground = OfficePalette::color(OfficePalette::Background);
    const QColor& colorForeground = OfficePalette::color(OfficePalette::DisabledText);
    const QColor& colorAccent = OfficeAccent::color(accent());

    // Drop shadow
    if (m_stateWindow != StateResize && isActive() && !isMaximized())
    {
        painter.drawPixmap(QPoint(), m_dropShadow);
    }

    // Background
    painter.fillRect(m_clientRectangle, colorBackground);

    // Border
    if (isActive())
    {
        painter.setPen(colorAccent);
    }
    else
    {
        painter.setPen(colorForeground);
    }

    painter.drawRect(m_clientRectangle.adjusted(0,0,-1,-1));
}

void OfficeWindow::resizeEvent(QResizeEvent* event)
{
    updateResizeRectangles();
    updateLayoutPadding();
    updateResizeWidgets();

    // Does not generate a drop shadow if resizing or currently being in
    // maximized window mode.
    if (m_stateWindow != StateResize && !isMaximized())
    {
        // Little hack: When the window is really big, repainting the drop
        // shadow takes long, causing layouts, button rectangles and other
        // contents to be redrawn late, causing a visual glitch.
        repaint();

        generateDropShadow();
    }

    update();

    QWidget::resizeEvent(event);
}

void OfficeWindow::focusInEvent(QFocusEvent*)
{
    if (g_activeWindow != this)
    {
        g_activeWindow = this;
    }
}

void OfficeWindow::focusOutEvent(QFocusEvent*)
{
    if (g_activeWindow == this)
    {
        g_activeWindow = nullptr;
    }
}

void OfficeWindow::showEvent(QShowEvent* event)
{
    // When window is first shown, apply accent color to all widgets.
    setAccent(accent());
    updateLayoutPadding();
    updateResizeRectangles();

    QWidget::showEvent(event);
}

bool OfficeWindow::event(QEvent* event)
{
    switch (event->type())
    {
    case QEvent::WindowActivate:
        focusInEvent(nullptr);
        break;

    case QEvent::WindowDeactivate:
        focusOutEvent(nullptr);
        break;
    }

    return QWidget::event(event);
}

void OfficeWindow::generateDropShadow()
{
    m_dropShadow = OfficeImage::generateDropShadow(size());
}

void OfficeWindow::updateResizeRectangles()
{
    int padding  = (isMaximized()) ? 0 : c_shadowPadding;

    // Resize areas
    m_resizeTopLeft->setGeometry(0, 0, 10, 10);
    m_resizeTopRight->setGeometry(width() - 10, 0, 10, 10);
    m_resizeBottomRight->setGeometry(width() - 10, height() - 10, 10, 10);
    m_resizeBottomLeft->setGeometry(0, height() - 10, 10, 10);
    m_resizeTop->setGeometry(10, 0, width() - 20, 10);
    m_resizeRight->setGeometry(width() - 10, 10, 10, height() - 20);
    m_resizeBottom->setGeometry(10, height() - 10, width() - 20, 10);
    m_resizeLeft->setGeometry(0, 10, 10, height() - 20);

    m_clientRectangle.setRect(
        padding,
        padding,
        width()  - padding * 2,
        height() - padding * 2
        );

    m_titleBar->setGeometry(
        padding + 1,
        padding + 1,
        width() - padding * 2 - 2,
        c_titleHeight - 1
        );

    m_titleBar->updateRectangles();
    m_titleBar->updateVisibleTitle();
}

void OfficeWindow::updateResizeWidgets()
{
    if (OffHasFlag(m_flagsWindow, NoResize) || isMaximized())
    {
        if (m_resizeTopLeft->isVisible()) m_resizeTopLeft->hide();
        if (m_resizeTopRight->isVisible()) m_resizeTopRight->hide();
        if (m_resizeBottomRight->isVisible()) m_resizeBottomRight->hide();
        if (m_resizeBottomLeft->isVisible()) m_resizeBottomLeft->hide();
        if (m_resizeTop->isVisible()) m_resizeTop->hide();
        if (m_resizeLeft->isVisible()) m_resizeLeft->hide();
        if (m_resizeBottom->isVisible()) m_resizeBottom->hide();
        if (m_resizeRight->isVisible()) m_resizeRight->hide();
    }
    else
    {
        if (!m_resizeTopLeft->isVisible()) m_resizeTopLeft->show();
        if (!m_resizeTopRight->isVisible()) m_resizeTopRight->show();
        if (!m_resizeBottomRight->isVisible()) m_resizeBottomRight->show();
        if (!m_resizeBottomLeft->isVisible()) m_resizeBottomLeft->show();
        if (!m_resizeTop->isVisible()) m_resizeTop->show();
        if (!m_resizeLeft->isVisible()) m_resizeLeft->show();
        if (!m_resizeBottom->isVisible()) m_resizeBottom->show();
        if (!m_resizeRight->isVisible()) m_resizeRight->show();
    }
}

void OfficeWindow::updateLayoutPadding()
{
    if (layout() != nullptr)
    {
        if (isMaximized())
        {
            // No drop shadow in maximize mode.
            layout()->setContentsMargins(1, c_titleHeight, 1, 1);
        }
        else
        {
            layout()->setContentsMargins(
                c_shadowPadding + 1,
                c_titleHeight + c_shadowPadding,
                c_shadowPadding + 1,
                c_shadowPadding + 1
                );
        }
    }
}

bool OfficeWindow::isActive() const
{
    return isActiveWindow() || m_tooltipVisible;
}
