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

#pragma once
#ifndef QOFFICE_WIDGETS_DIALOGS_OFFICEWINDOWTITLEBAR_HPP
#define QOFFICE_WIDGETS_DIALOGS_OFFICEWINDOWTITLEBAR_HPP

#include <QOffice/Widgets/OfficeWindowMenu.hpp>
#include <QWidget>

class OfficeWindow;

namespace priv
{
class ResizeArea;
class Titlebar : public QWidget
{
public:

    enum ButtonState
    {
        ButtonNone,
        ButtonHover,
        ButtonPress,
        ButtonSpecial
    };


    OffDefaultDtor(Titlebar)
    OffDisableCopy(Titlebar)
    OffDisableMove(Titlebar)

    Titlebar(OfficeWindow* window);

protected:

    void paintEvent(QPaintEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;
    void mouseDoubleClickEvent(QMouseEvent*) override;
    void leaveEvent(QEvent*) override;

private:

    ////////////////////////////////////////////////////////////////////////////
    // Functions
    //
    ////////////////////////////////////////////////////////////////////////////
    void updateRectangles(); // drag rect too
    void updateVisibleTitle();
    bool mouseMoveDrag(const QPoint&);
    bool mouseMoveSpecial(const QPoint&);
    bool mouseMoveHitTest(const QPoint&);
    bool mousePressDrag(const QPoint&);
    bool mousePressHitTest(const QPoint&);
    bool mouseReleaseDrag(const QPoint&);
    bool mouseReleaseAction(const QPoint&);
    QRect centerRectangle(const QPixmap&, const QRect&);

    ////////////////////////////////////////////////////////////////////////////
    // Members
    //
    ////////////////////////////////////////////////////////////////////////////
    OfficeWindow*     m_window;
    OfficeWindowMenu* m_windowLabelMenu;
    OfficeWindowMenu* m_windowQuickMenu;
    ButtonState       m_stateClose;
    ButtonState       m_stateMaximize;
    ButtonState       m_stateMinimize;
    QPixmap           m_imageClose;
    QPixmap           m_imageMaximize;
    QPixmap           m_imageMinimize;
    QPixmap           m_imageRestore;
    QString           m_visibleTitle;
    QPoint            m_dragPosition;
    QRect             m_titleRectangle;
    QRect             m_dragRectangle;
    QRect             m_closeRectangle;
    QRect             m_maximizeRectangle;
    QRect             m_minimizeRectangle;

    friend class OfficeWindow;
    friend class OfficeWindowMenu;
    friend class priv::ResizeArea;

};
}

#endif
