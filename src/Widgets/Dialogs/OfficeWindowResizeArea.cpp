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

#include <QOffice/Widgets/Dialogs/OfficeWindow.hpp>
#include <QOffice/Widgets/Dialogs/OfficeWindowResizeArea.hpp>

#include <QtEvents>

priv::ResizeArea::ResizeArea(OfficeWindow* window, int directions)
    : QWidget(window)
    , m_window(window)
    , m_directions(directions)
{
    // Determines which QCursor to use. The concept of the resize area is as
    // follows: If the mouse pointer enters one of the resize areas on the
    // window, a QWidget::enterEvent is emitted, causing the global cursor
    // to change to the widget's one. Without using this method, we may get
    // glitches when we do normal hit tests in the window class while moving
    // the mouse pointer rapidly.
    if (OffHasFlag(directions, OfficeWindow::ResizeBottom) &&
        OffHasFlag(directions, OfficeWindow::ResizeLeft))
    {
        setCursor(Qt::SizeBDiagCursor);
    }
    else if (OffHasFlag(directions, OfficeWindow::ResizeBottom) &&
             OffHasFlag(directions, OfficeWindow::ResizeRight))
    {
        setCursor(Qt::SizeFDiagCursor);
    }
    else if (OffHasFlag(directions, OfficeWindow::ResizeTop) &&
             OffHasFlag(directions, OfficeWindow::ResizeLeft))
    {
        setCursor(Qt::SizeFDiagCursor);
    }
    else if (OffHasFlag(directions, OfficeWindow::ResizeTop) &&
             OffHasFlag(directions, OfficeWindow::ResizeRight))
    {
        setCursor(Qt::SizeBDiagCursor);
    }
    else if (OffHasFlag(directions, OfficeWindow::ResizeLeft) ||
             OffHasFlag(directions, OfficeWindow::ResizeRight))
    {
        setCursor(Qt::SizeHorCursor);
    }
    else if (OffHasFlag(directions, OfficeWindow::ResizeTop) ||
             OffHasFlag(directions, OfficeWindow::ResizeBottom))
    {
        setCursor(Qt::SizeVerCursor);
    }
}

void priv::ResizeArea::enterEvent(QEvent*)
{
    // When entering a resize area, no button should be highlighted.
    m_window->m_stateClose    = OfficeWindow::ButtonNone;
    m_window->m_stateMaximize = OfficeWindow::ButtonNone;
    m_window->m_stateMinimize = OfficeWindow::ButtonNone;

    // Applies the changes we just did visually.
    m_window->repaintTitleBar();
}

void priv::ResizeArea::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && m_window->canResize())
    {
        m_window->m_stateWindow = OfficeWindow::StateResize;
    }
}

void priv::ResizeArea::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && m_window->canResize())
    {
        m_window->m_stateWindow = OfficeWindow::StateNone;
        m_window->generateDropShadow();
        m_window->update();
    }
}

void priv::ResizeArea::mouseMoveEvent(QMouseEvent* event)
{
    if (m_window->m_stateWindow == OfficeWindow::StateResize)
    {
        QPoint posGlobal = event->globalPos();
        QRect windowRect = m_window->geometry();
        QRect originRect = m_window->geometry();
        QSize minSize    = m_window->minimumSize();
        QSize maxSize    = m_window->maximumSize();

        if (OffHasFlag(m_directions, OfficeWindow::ResizeLeft))
            windowRect.setLeft(posGlobal.x());
        if (OffHasFlag(m_directions, OfficeWindow::ResizeRight))
            windowRect.setRight(posGlobal.x());
        if (OffHasFlag(m_directions, OfficeWindow::ResizeBottom))
            windowRect.setBottom(posGlobal.y());
        if (OffHasFlag(m_directions, OfficeWindow::ResizeTop))
            windowRect.setTop(posGlobal.y());

        // If we by any chance are about to exceed the maximum or minimum size,
        // we have to reset the geometry in one or another direction.
        if (windowRect.width() < minSize.width() ||
            windowRect.width() > maxSize.width())
        {
            windowRect.setLeft(originRect.left());
            windowRect.setRight(originRect.right());
        }

        if (windowRect.height() < minSize.height() ||
            windowRect.height() > maxSize.height())
        {
            windowRect.setTop(originRect.top());
            windowRect.setBottom(originRect.bottom());
        }

        // While the user clicks and drags a resize area simutaneously, we have
        // to resize the entire window as fast as possible, otherwise the mouse
        // pointer leaves the resize widget and we get an undesirable effect.
        // QWidget::setGeometry seems to resize the widget fast enough.
        m_window->setGeometry(windowRect);
    }
}
