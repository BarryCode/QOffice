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
#ifndef QOFFICE_WIDGETS_DIALOGS_OFFICEWINDOW_HPP
#define QOFFICE_WIDGETS_DIALOGS_OFFICEWINDOW_HPP

#include <QOffice/Widgets/OfficeWidget.hpp>
#include <QOffice/Widgets/OfficeWindowMenu.hpp>
#include <QOffice/Widgets/Dialogs/OfficeWindowResizeArea.hpp>

////////////////////////////////////////////////////////////////////////////////
/// \class OfficeWindow
/// \brief This class defines a window in a modern look and feel.
/// \author Nicolas Kogler (nicolas.kogler@hotmail.com)
/// \date September 24, 2017
///
////////////////////////////////////////////////////////////////////////////////
class QOFFICE_WIDGET_API OfficeWindow : public QWidget, public OfficeWidget
{
public:

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Defines flags that can modify the behaviour of OfficeWindow.
    /// \enum Flag
    ///
    ////////////////////////////////////////////////////////////////////////////
    enum Flags
    {
        NoFlag           = 0x0000,
        NoCloseButton    = 0x0001,
        NoMinimizeButton = 0x0002,
        NoMaximizeButton = 0x0004,
        NoResize         = 0x0008,
        NoMaximize       = 0x0010,
        NoMenu           = 0x0020
    };

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Defines the states for the window buttons in the top-right.
    /// \enum ButtonState
    ///
    ////////////////////////////////////////////////////////////////////////////
    enum ButtonState
    {
        ButtonNone,
        ButtonHover,
        ButtonPress,
        ButtonSpecial
    };

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Defines the states for various window actions.
    /// \enum WindowState
    ///
    ////////////////////////////////////////////////////////////////////////////
    enum WindowState
    {
        StateNone,
        StateDrag,
        StateResize
    };

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Defines the resize directions for the window.
    /// \enum ResizeDirection
    ///
    ////////////////////////////////////////////////////////////////////////////
    enum ResizeDirection
    {
        ResizeNone   = 0x0000,
        ResizeLeft   = 0x0001,
        ResizeTop    = 0x0002,
        ResizeRight  = 0x0004,
        ResizeBottom = 0x0008
    };

    OffDefaultDtor(OfficeWindow)
    OffDisableCopy(OfficeWindow)
    OffDisableMove(OfficeWindow)

    ////////////////////////////////////////////////////////////////////////////
    /// Initializes a new instance of OfficeWindow and specifies the given
    /// \p parent as parent window.
    ///
    /// \param[in] parent The parent window of this window.
    ///
    ////////////////////////////////////////////////////////////////////////////
    OfficeWindow(QWidget* parent = nullptr);

    ////////////////////////////////////////////////////////////////////////////
    /// Determines whether this window has a close button.
    ///
    /// \return True if it has a close button, false otherwise.
    ///
    /// \sa OfficeWindow::setFlags OfficeWindow::setCloseButtonVisible
    ///
    ////////////////////////////////////////////////////////////////////////////
    bool hasCloseButton() const;

    ////////////////////////////////////////////////////////////////////////////
    /// Determines whether this window has a maximize button.
    ///
    /// \return True if it has a maximize button, false otherwise.
    ///
    /// \sa  OfficeWindow::flags OfficeWindow::setMaximizeButtonVisible
    ///
    ////////////////////////////////////////////////////////////////////////////
    bool hasMaximizeButton() const;

    ////////////////////////////////////////////////////////////////////////////
    /// Determines whether this window has a minimize button.
    ///
    /// \return True if it has a minimize button, false otherwise.
    ///
    /// \sa  OfficeWindow::flags OfficeWindow::setMinimizeButtonVisible
    ///
    ////////////////////////////////////////////////////////////////////////////
    bool hasMinimizeButton() const;

    ////////////////////////////////////////////////////////////////////////////
    /// Determines whether this window can be resized.
    ///
    /// \return True if it can be resized, false otherwise.
    ///
    /// \sa OfficeWindow::flags OfficeWindow::setFlags
    ///
    ////////////////////////////////////////////////////////////////////////////
    bool canResize() const;

    ////////////////////////////////////////////////////////////////////////////
    /// Determines whether this window is active.
    ///
    /// \return True if it is active, false otherwise.
    ///
    ////////////////////////////////////////////////////////////////////////////
    bool isActive() const;

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the current flags of this OfficeWindow.
    ///
    /// \return A bitwise OR combination of OfficeWindow::Flags values.
    ///
    /// \sa OfficeWindow::setFlags
    ///
    ////////////////////////////////////////////////////////////////////////////
    Flags flags() const;

    ////////////////////////////////////////////////////////////////////////////
    /// Specifies the accent for all widgets subordinated to this window.
    ///
    /// \param[in] accent The new accent to apply to all widgets.
    ///
    /// \sa OfficeWidget::accent
    ///
    ////////////////////////////////////////////////////////////////////////////
    void setAccent(Office::Accent accent) override;

    ////////////////////////////////////////////////////////////////////////////
    /// Specifies whether the window has a close button or not.
    ///
    /// \param[in] visible True to show the close button.
    ///
    /// \sa OfficeWindow::hasCloseButton OfficeWindow::setFlags
    ///
    ////////////////////////////////////////////////////////////////////////////
    void setCloseButtonVisible(bool visible);

    ////////////////////////////////////////////////////////////////////////////
    /// Specifies whether the window has a maximize button or not.
    ///
    /// \param[in] visible True to show the maximize button.
    ///
    /// \sa OfficeWindow::hasMaximizeButton OfficeWindow::setFlags
    ///
    ////////////////////////////////////////////////////////////////////////////
    void setMaximizeButtonVisible(bool visible);

    ////////////////////////////////////////////////////////////////////////////
    /// Specifies whether the window has a minimize button or not.
    ///
    /// \param[in] visible True to show the minimize button.
    ///
    /// \sa OfficeWindow::hasMinimizeButton OfficeWindow::setFlags
    ///
    ////////////////////////////////////////////////////////////////////////////
    void setMinimizeButtonVisible(bool visible);

    ////////////////////////////////////////////////////////////////////////////
    /// Specifies whether the window is resizable.
    ///
    /// \param[in] resizable True to be able to resize window.
    ///
    /// \sa OfficeWindow::canResize OfficeWindow::setFlags
    ///
    ////////////////////////////////////////////////////////////////////////////
    void setResizable(bool resizable);

    ////////////////////////////////////////////////////////////////////////////
    /// Specifies the flags for this office window. The flags specify window
    /// button visibility, resize capability and more. Multiple flags can be
    /// specified by bitwise OR'ing multiple OfficeWindow::Flags values together.
    ///
    /// \param[in] flags The new flags.
    ///
    /// \sa OfficeWindow::flags
    ///
    ////////////////////////////////////////////////////////////////////////////
    void setFlags(Flags flags);

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the currently active window.
    ///
    /// \return The active window or nullptr.
    ///
    ////////////////////////////////////////////////////////////////////////////
    static OfficeWindow* activeWindow();

protected:

    virtual void paintEvent(QPaintEvent*) override;
    virtual void resizeEvent(QResizeEvent*) override;
    virtual void mouseMoveEvent(QMouseEvent*) override;
    virtual void mousePressEvent(QMouseEvent*) override;
    virtual void mouseReleaseEvent(QMouseEvent*) override;
    virtual void mouseDoubleClickEvent(QMouseEvent*) override;
    virtual void focusInEvent(QFocusEvent*) override;
    virtual void focusOutEvent(QFocusEvent*) override;
    virtual void showEvent(QShowEvent*) override;
    virtual void leaveEvent(QEvent*) override;
    virtual bool event(QEvent*) override;

private:

    ////////////////////////////////////////////////////////////////////////////
    // Functions
    //
    ////////////////////////////////////////////////////////////////////////////
    void generateDropShadow();
    void repaintTitleBar();
    void updateButtonRectangles();
    void updateResizeRectangles();
    void updateVisibleTitle();
    void updateResizeWidgets();
    void updateLayoutPadding();
    bool mouseMoveDrag(const QPoint&);
    bool mouseMoveSpecial(const QPoint&);
    bool mouseMoveHitTest(const QPoint&);
    bool mousePressDrag(const QPoint&);
    bool mousePressHitTest(const QPoint&);
    bool mouseReleaseDrag(const QPoint&);
    bool mouseReleaseAction(const QPoint&);
    QRect centerRectangle(const QPixmap&, const QRect&);

    ////////////////////////////////////////////////////////////////////////////
    // Members 1
    //
    ////////////////////////////////////////////////////////////////////////////
    ButtonState m_stateClose;
    ButtonState m_stateMaximize;
    ButtonState m_stateMinimize;
    WindowState m_stateWindow;
    Flags       m_flagsWindow;
    QPixmap     m_dropShadow;
    QPixmap     m_imageClose;
    QPixmap     m_imageMaximize;
    QPixmap     m_imageMinimize;
    QPixmap     m_imageRestore;
    QString     m_visibleTitle;
    QPoint      m_dragPosition;
    QRect       m_clientRectangle;
    QRect       m_titleRectangle;
    QRect       m_dragRectangle;
    QRect       m_closeRectangle;
    QRect       m_maximizeRectangle;
    QRect       m_minimizeRectangle;
    bool        m_tooltipVisible;

    ////////////////////////////////////////////////////////////////////////////
    // Members 2
    //
    ////////////////////////////////////////////////////////////////////////////
    priv::ResizeArea* m_resizeTopLeft;
    priv::ResizeArea* m_resizeTopRight;
    priv::ResizeArea* m_resizeBottomLeft;
    priv::ResizeArea* m_resizeBottomRight;
    priv::ResizeArea* m_resizeTop;
    priv::ResizeArea* m_resizeLeft;
    priv::ResizeArea* m_resizeBottom;
    priv::ResizeArea* m_resizeRight;
    OfficeWindowMenu* m_windowLabelMenu;
    OfficeWindowMenu* m_windowQuickMenu;

    ////////////////////////////////////////////////////////////////////////////
    // Metadata
    //
    ////////////////////////////////////////////////////////////////////////////
    Q_OBJECT
    Q_PROPERTY(bool Resizable READ canResize WRITE setResizable)
    Q_PROPERTY(bool CloseButton READ hasCloseButton WRITE setCloseButtonVisible)
    Q_PROPERTY(bool MaximizeButton READ hasMaximizeButton WRITE setMaximizeButtonVisible)
    Q_PROPERTY(bool MinimizeButton READ hasMinimizeButton WRITE setMinimizeButtonVisible)
    Q_PROPERTY(Office::Accent Accent READ accent WRITE setAccent)

    friend class priv::ResizeArea;
    friend class OfficeTooltip;
};

OffEnumOperators(OfficeWindow::Flags)
OffEnumOperators(OfficeWindow::ResizeDirection)

#endif

////////////////////////////////////////////////////////////////////////////////
/// \class OfficeWindow
/// \ingroup Widget
///
/// $Detailedclassdesc
///
/// \code
/// <example_code>
/// \endcode
///
////////////////////////////////////////////////////////////////////////////////
