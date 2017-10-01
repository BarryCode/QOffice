////////////////////////////////////////////////////////////////////////////////
//
// QOffice - The office framework for Qt
// Copyright (C) 2016-2018 Nicolas Kogler
//
// This file is part of the $Module module.
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
#include <QOffice/Widgets/Dialogs/OfficeWindowTitlebar.hpp>

#include <QPainter>
#include <QtEvents>

OffAnonymous(QOFFICE_CONSTEXPR int c_titlePaddingX = 24)
OffAnonymous(QOFFICE_CONSTEXPR int c_titlePaddingY = 10)
OffAnonymous(QOFFICE_CONSTEXPR int c_windowButtonX = 10)
OffAnonymous(QOFFICE_CONSTEXPR int c_windowButtonY = 8)

priv::Titlebar::Titlebar(OfficeWindow* window)
    : QWidget(window)
    , m_window(window)
    , m_windowLabelMenu(new OfficeWindowMenu(this, OfficeWindowMenu::LabelMenu))
    , m_windowQuickMenu(new OfficeWindowMenu(this, OfficeWindowMenu::QuickMenu))
    , m_stateClose(ButtonNone)
    , m_stateMaximize(ButtonNone)
    , m_stateMinimize(ButtonNone)
    , m_imageClose(QPixmap(":/qoffice/images/window/close.png"))
    , m_imageMaximize(QPixmap(":/qoffice/images/window/max.png"))
    , m_imageMinimize(QPixmap(":/qoffice/images/window/min.png"))
    , m_imageRestore(QPixmap(":/qoffice/images/window/restore.png"))
{
    setMouseTracking(true);
}

void priv::Titlebar::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    Office::Accent accent = m_window->accent();

    // Background
    painter.fillRect(m_titleRectangle, OfficeAccent::color(accent));

    // Titlebar text
    if (!m_window->isActive())
    {
        // When the window is not active, the titlebar text and the titlebar
        // buttons should not be rendered darker but rather blend into the
        // background.
        painter.setOpacity(0.5);
    }

    painter.setFont(font());
    painter.setPen(OfficePalette::color(OfficePalette::Background));
    painter.drawText(m_titleRectangle, m_visibleTitle, QTextOption(Qt::AlignCenter));

    // Window button background
    if (m_stateClose == ButtonHover)
        painter.fillRect(m_closeRectangle, OfficeAccent::lightColor(accent));
    else if (m_stateMaximize == ButtonHover)
        painter.fillRect(m_maximizeRectangle, OfficeAccent::lightColor(accent));
    else if (m_stateMinimize == ButtonHover)
        painter.fillRect(m_minimizeRectangle, OfficeAccent::lightColor(accent));
    else if (m_stateClose == ButtonPress)
        painter.fillRect(m_closeRectangle, OfficeAccent::darkColor(accent));
    else if (m_stateMaximize == ButtonPress)
        painter.fillRect(m_maximizeRectangle, OfficeAccent::darkColor(accent));
    else if (m_stateMinimize == ButtonPress)
        painter.fillRect(m_minimizeRectangle, OfficeAccent::darkColor(accent));

    // Window button icons
    if (OffHasNotFlag(m_window->m_flagsWindow, OfficeWindow::NoCloseButton))
    {
        painter.drawPixmap(centerRectangle(m_imageClose, m_closeRectangle), m_imageClose);
    }
    if (OffHasNotFlag(m_window->m_flagsWindow, OfficeWindow::NoMinimizeButton))
    {
        painter.drawPixmap(centerRectangle(m_imageMinimize, m_minimizeRectangle), m_imageMinimize);
    }
    if (OffHasNotFlag(m_window->m_flagsWindow, OfficeWindow::NoMaximizeButton))
    {
        if (m_window->isMaximized())
        {
            painter.drawPixmap(centerRectangle(m_imageRestore, m_maximizeRectangle), m_imageRestore);
        }
        else
        {
            painter.drawPixmap(centerRectangle(m_imageMaximize, m_maximizeRectangle), m_imageMaximize);
        }
    }
}

void priv::Titlebar::mouseMoveEvent(QMouseEvent* event)
{
    const QPoint pos = event->pos();

    // Performs several hit-tests. If one of these functions returns true,
    // the title bar will be redrawn.
    if (!mouseMoveDrag(pos))
    {
        if (mouseMoveSpecial(pos) || mouseMoveHitTest(pos))
        {
            update();
        }
    }

    QWidget::mouseMoveEvent(event);
}

void priv::Titlebar::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        const QPoint pos = event->pos();
        if (mousePressDrag(pos))
        {
            return;
        }

        if (mousePressHitTest(pos))
        {
            update();
        }
    }

    QWidget::mousePressEvent(event);
}

void priv::Titlebar::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        const QPoint pos = event->pos();
        if (mouseReleaseDrag(pos))
        {
            return;
        }

        if (mouseReleaseAction(pos))
        {
            update();
        }
    }

    QWidget::mouseReleaseEvent(event);
}

void priv::Titlebar::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton &&
        m_dragRectangle.contains(event->pos()) &&
        m_window->hasMaximizeButton() &&
        m_window->canResize())
    {
        // The window is about to be maximized or restored. In order to
        // avoid that all the titlebar's contents are invisible for a split
        // second, we recalculate all the necessary things beforehand.
        updateRectangles();
        updateVisibleTitle();
        m_window->updateResizeRectangles();

        if (m_window->isMaximized())
        {
            m_window->showNormal();
        }
        else
        {
            m_window->showMaximized();
        }

        m_stateMaximize = ButtonNone;
        m_window->update();
        update();
    }

    m_window->updateLayoutPadding();
}

void priv::Titlebar::leaveEvent(QEvent* event)
{
    if (m_window->m_stateWindow == OfficeWindow::StateDrag)
    {
        // There might be a chance of the mouse pointer leaving the window
        // while we are dragging it.
        m_window->move(QCursor::pos() - m_dragPosition);
    }
    else
    {
        m_stateClose    = ButtonNone;
        m_stateMaximize = ButtonNone;
        m_stateMinimize = ButtonNone;

        update();
    }

    QWidget::leaveEvent(event);
}

void priv::Titlebar::updateRectangles()
{
    const QSize& sizeClose = m_imageClose.size();
    const QSize& sizeMaxim = m_imageMaximize.size();
    const QSize& sizeMinim = m_imageMinimize.size();

    // Initial button position.
    int initialX = width() - sizeClose.width() - c_windowButtonX;
    int initialY = c_windowButtonY;

    int totalWidth =
        m_closeRectangle.width()    +
        m_maximizeRectangle.width() +
        m_minimizeRectangle.width();

    int dragWidth =
        width()     -
        totalWidth  -
        m_windowLabelMenu->width() -
        m_windowQuickMenu->width();

    // Close button rectangle
    if (OffHasNotFlag(m_window->m_flagsWindow, OfficeWindow::NoCloseButton))
    {
        m_closeRectangle.setRect(
            initialX - 10,
            initialY - 8,
            sizeClose.width()  + 20,
            sizeClose.height() + 16
            );

        initialX -= sizeMaxim.width() + 20;
    }

    // Maximize button rectangle
    if (OffHasNotFlag(m_window->m_flagsWindow, OfficeWindow::NoMaximizeButton))
    {
        m_maximizeRectangle.setRect(
            initialX - 10,
            initialY - 8,
            sizeMaxim.width()  + 20,
            sizeMaxim.height() + 16
            );

        initialX -= sizeMinim.width() + 20;
    }

    // Minimize button rectangle
    if (OffHasNotFlag(m_window->m_flagsWindow, OfficeWindow::NoMinimizeButton))
    {
        m_minimizeRectangle.setRect(
            initialX - 10,
            initialY - 8,
            sizeMinim.width()  + 20,
            sizeMinim.height() + 16
            );
    }

    // Misc rectangles
    m_dragRectangle.setRect(m_windowQuickMenu->width(), 0, dragWidth, height());
    m_titleRectangle.setRect(0, 0, width(), height());
    m_windowLabelMenu->move(m_dragRectangle.x() + m_dragRectangle.width(), 0);
    m_windowQuickMenu->move(0, 0);
}

void priv::Titlebar::updateVisibleTitle()
{
    QString title = m_window->windowTitle();
    QFontMetrics metrics(font());

    int currentWidth = metrics.width(title);
    int estimatedWidth = m_dragRectangle.width() - c_titlePaddingX * 2 - currentWidth;

    // Removes characters as long as it does not overlap the window buttons.
    while (currentWidth > estimatedWidth && estimatedWidth > 0)
    {
        title.remove(title.length() - 1, 1);
        currentWidth = metrics.width(title);
    }

    // Displays dots behind the modified title.
    if (title.length() < 3 || estimatedWidth < currentWidth)
    {
        title = "";
    }
    else if (m_window->windowTitle().length() != title.length())
    {
        title.remove(title.length() - 2, 2).append("...");
    }

    m_visibleTitle = title;
}

bool priv::Titlebar::mouseMoveDrag(const QPoint& pos)
{
    if (m_window->m_stateWindow == OfficeWindow::StateDrag)
    {
        auto globalPos = m_window->mapToGlobal(pos);
        if (m_window->isMaximized())
        {
            m_stateMaximize = ButtonNone;
            m_window->m_stateWindow = OfficeWindow::StateNone;

            // The window is about to be restored. In order to avoid that all
            // the titlebar's contents are invisible for a split second, we
            // recalculate all the necessary things beforehand.
            m_window->updateLayoutPadding();
            m_window->updateResizeRectangles();

            m_window->showNormal();
        }
        else
        {
            m_window->move(globalPos - m_dragPosition);
            m_window->updateGeometry();
        }

        return true;
    }

    return false;
}

bool priv::Titlebar::mouseMoveSpecial(const QPoint& pos)
{
    // Special <> press
    if (m_stateClose == ButtonSpecial && m_closeRectangle.contains(pos))
    {
        m_stateClose = ButtonPress;
        return true;
    }
    else if (m_stateMaximize == ButtonSpecial && m_maximizeRectangle.contains(pos))
    {
        m_stateMaximize = ButtonPress;
        return true;
    }
    else if (m_stateMinimize == ButtonSpecial && m_minimizeRectangle.contains(pos))
    {
        m_stateMinimize = ButtonPress;
        return true;
    }

    // Press <> special
    if (m_stateClose == ButtonPress && !m_closeRectangle.contains(pos))
    {
        m_stateClose = ButtonSpecial;
        return true;
    }
    else if (m_stateMaximize == ButtonPress && !m_maximizeRectangle.contains(pos))
    {
        m_stateMaximize = ButtonSpecial;
        return true;
    }
    else if (m_stateMinimize == ButtonPress && !m_minimizeRectangle.contains(pos))
    {
        m_stateMinimize = ButtonSpecial;
        return true;
    }

    return false;
}

bool priv::Titlebar::mouseMoveHitTest(const QPoint& pos)
{
    // Changes the button into hovered state if the mouse pointer happens to
    // hover it.
    if (m_stateClose    != ButtonPress   &&
        m_stateClose    != ButtonSpecial &&
        m_stateMaximize != ButtonPress   &&
        m_stateMaximize != ButtonSpecial &&
        m_stateMinimize != ButtonPress   &&
        m_stateMinimize != ButtonSpecial)
    {
        // Determines whether one button has been hovered before. If yes, do not
        // perform a repaint of the title bar.
        bool state = m_stateClose    != ButtonHover &&
                     m_stateMaximize != ButtonHover &&
                     m_stateMinimize != ButtonHover;

        m_stateClose    = ButtonNone;
        m_stateMaximize = ButtonNone;
        m_stateMinimize = ButtonNone;

        if (OffHasNotFlag(m_window->m_flagsWindow, OfficeWindow::NoCloseButton) &&
            m_closeRectangle.contains(pos))
        {
            m_stateClose = ButtonHover;
            return true;
        }
        else if (OffHasNotFlag(m_window->m_flagsWindow, OfficeWindow::NoMaximizeButton) &&
            m_maximizeRectangle.contains(pos))
        {
            m_stateMaximize = ButtonHover;
            return true;
        }
        else if (OffHasNotFlag(m_window->m_flagsWindow, OfficeWindow::NoMinimizeButton) &&
            m_minimizeRectangle.contains(pos))
        {
            m_stateMinimize = ButtonHover;
            return true;
        }

        return state;
    }

    return false;
}

bool priv::Titlebar::mousePressDrag(const QPoint& pos)
{
    // Activates dragging if the dragging rectangle is being pressed and
    // moved later on.
    if (m_dragRectangle.contains(pos))
    {
        m_dragPosition = pos;
        m_window->m_stateWindow = OfficeWindow::StateDrag;

        return true;
    }

    return false;
}

bool priv::Titlebar::mousePressHitTest(const QPoint& pos)
{
    bool state = m_stateClose    != ButtonPress &&
                 m_stateMaximize != ButtonPress &&
                 m_stateMinimize != ButtonPress;

    m_stateClose    = ButtonNone;
    m_stateMaximize = ButtonNone;
    m_stateMinimize = ButtonNone;

    if (OffHasNotFlag(m_window->m_flagsWindow, OfficeWindow::NoCloseButton) &&
        m_closeRectangle.contains(pos))
    {
        m_stateClose = ButtonPress;
        return true;
    }
    else if (OffHasNotFlag(m_window->m_flagsWindow, OfficeWindow::NoMaximizeButton) &&
        m_maximizeRectangle.contains(pos))
    {
        m_stateMaximize = ButtonPress;
        return true;
    }
    else if (OffHasNotFlag(m_window->m_flagsWindow, OfficeWindow::NoMinimizeButton) &&
        m_minimizeRectangle.contains(pos))
    {
        m_stateMinimize = ButtonPress;
        return true;
    }

    return state;
}

bool priv::Titlebar::mouseReleaseDrag(const QPoint&)
{
    if (m_window->m_stateWindow == OfficeWindow::StateDrag)
    {
        m_window->m_stateWindow = OfficeWindow::StateNone;

        return true;
    }

    return false;
}

bool priv::Titlebar::mouseReleaseAction(const QPoint& pos)
{
    if (m_stateClose    == ButtonPress   ||
        m_stateClose    == ButtonSpecial ||
        m_stateMaximize == ButtonPress   ||
        m_stateMaximize == ButtonSpecial ||
        m_stateMinimize == ButtonPress   ||
        m_stateMinimize == ButtonSpecial)
    {
        if (m_stateClose == ButtonPress && m_closeRectangle.contains(pos))
        {
            m_window->close();
        }
        else if (m_stateMaximize == ButtonPress && m_maximizeRectangle.contains(pos))
        {
            // The window is about to be maximized or restored. In order to
            // avoid that all the titlebar's contents are invisible for a split
            // second, we recalculate all the necessary things beforehand.
            updateRectangles();
            updateVisibleTitle();
            m_window->updateResizeRectangles();

            if (m_window->isMaximized())
            {
                m_window->showNormal();
            }
            else
            {
                m_window->showMaximized();
            }

            m_window->updateLayoutPadding();
        }
        else if (m_stateMinimize == ButtonPress && m_minimizeRectangle.contains(pos))
        {
            m_window->updateLayoutPadding();
            m_window->showMinimized();
        }

        m_stateClose    = ButtonNone;
        m_stateMaximize = ButtonNone;
        m_stateMinimize = ButtonNone;

        return true;
    }

    return false;
}

QRect priv::Titlebar::centerRectangle(const QPixmap& pm, const QRect& rc)
{
    int dx = (rc.width()  - pm.width())  / 2;
    int dy = (rc.height() - pm.height()) / 2;

    return QRect(rc.x() + dx, rc.y() + dy, pm.width(), pm.height());
}
