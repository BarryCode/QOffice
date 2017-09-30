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

OffAnonymous(QOFFICE_CONSTEXPR OfficeWindow::ResizeDirection c_topLeft = OfficeWindow::ResizeTop | OfficeWindow::ResizeLeft)
OffAnonymous(QOFFICE_CONSTEXPR OfficeWindow::ResizeDirection c_topRight = OfficeWindow::ResizeTop | OfficeWindow::ResizeRight)
OffAnonymous(QOFFICE_CONSTEXPR OfficeWindow::ResizeDirection c_bottomLeft = OfficeWindow::ResizeBottom | OfficeWindow::ResizeLeft)
OffAnonymous(QOFFICE_CONSTEXPR OfficeWindow::ResizeDirection c_bottomRight = OfficeWindow::ResizeBottom | OfficeWindow::ResizeRight)
OffAnonymous(QOFFICE_CONSTEXPR OfficeWindow::ResizeDirection c_top = OfficeWindow::ResizeTop)
OffAnonymous(QOFFICE_CONSTEXPR OfficeWindow::ResizeDirection c_left = OfficeWindow::ResizeLeft)
OffAnonymous(QOFFICE_CONSTEXPR OfficeWindow::ResizeDirection c_bottom = OfficeWindow::ResizeBottom)
OffAnonymous(QOFFICE_CONSTEXPR OfficeWindow::ResizeDirection c_right = OfficeWindow::ResizeRight)

OffAnonymous(QOFFICE_CONSTEXPR int c_titlePaddingX = 24)
OffAnonymous(QOFFICE_CONSTEXPR int c_titlePaddingY = 10)
OffAnonymous(QOFFICE_CONSTEXPR int c_windowButtonX = 11)
OffAnonymous(QOFFICE_CONSTEXPR int c_windowButtonY = 9)
OffAnonymous(QOFFICE_CONSTEXPR int c_titleHeight   = 28)
OffAnonymous(QOFFICE_CONSTEXPR int c_menuItemSpacing = 16)
OffAnonymous(QOFFICE_CONSTEXPR int c_menuItemHeight  = 16)
OffAnonymous(QOFFICE_CONSTEXPR int c_menuIconY = 6)
OffAnonymous(QOFFICE_CONSTEXPR int c_iconPosX  = c_windowButtonX + c_shadowPadding)
OffAnonymous(QOFFICE_CONSTEXPR int c_iconPosY  = c_windowButtonY + c_shadowPadding)

OfficeWindow::OfficeWindow(QWidget* parent)
    : QWidget(parent)
    , m_stateClose(ButtonNone)
    , m_stateMaximize(ButtonNone)
    , m_stateMinimize(ButtonNone)
    , m_stateWindow(StateNone)
    , m_flagsWindow(NoFlag)
    , m_imageClose(QPixmap(":/qoffice/images/window/close.png"))
    , m_imageMaximize(QPixmap(":/qoffice/images/window/max.png"))
    , m_imageMinimize(QPixmap(":/qoffice/images/window/min.png"))
    , m_imageRestore(QPixmap(":/qoffice/images/window/restore.png"))
    , m_tooltipVisible(false)
    , m_resizeTopLeft(new priv::ResizeArea(this, c_topLeft))
    , m_resizeTopRight(new priv::ResizeArea(this, c_topRight))
    , m_resizeBottomLeft(new priv::ResizeArea(this, c_bottomLeft))
    , m_resizeBottomRight(new priv::ResizeArea(this, c_bottomRight))
    , m_resizeTop(new priv::ResizeArea(this, c_top))
    , m_resizeLeft(new priv::ResizeArea(this, c_left))
    , m_resizeBottom(new priv::ResizeArea(this, c_bottom))
    , m_resizeRight(new priv::ResizeArea(this, c_right))
    , m_windowLabelMenu(new OfficeWindowMenu(this, OfficeWindowMenu::LabelMenu))
    , m_windowQuickMenu(new OfficeWindowMenu(this, OfficeWindowMenu::QuickMenu))
{
    setGeometry(x(), y(), 600, 400);
    setMouseTracking(true);

    // Create a frameless window with a translucent background for the shadow.
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
    setAttribute(Qt::WA_TranslucentBackground);

    m_windowLabelMenu->show();
    m_windowQuickMenu->show();
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
    painter.fillRect(m_titleRectangle, colorAccent);

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

    // Titlebar text
    if (!isActive())
    {
        // When the window is not active, the titlebar text and the titlebar
        // buttons should not be rendered darker but rather blend into the
        // background.
        painter.setOpacity(0.5);
    }

    painter.setFont(font());
    painter.setPen(colorBackground);
    painter.drawText(m_titleRectangle, m_visibleTitle, QTextOption(Qt::AlignCenter));

    // Window button background
    if (m_stateClose == ButtonHover)
        painter.fillRect(m_closeRectangle, OfficeAccent::lightColor(accent()));
    else if (m_stateMaximize == ButtonHover)
        painter.fillRect(m_maximizeRectangle, OfficeAccent::lightColor(accent()));
    else if (m_stateMinimize == ButtonHover)
        painter.fillRect(m_minimizeRectangle, OfficeAccent::lightColor(accent()));
    else if (m_stateClose == ButtonPress)
        painter.fillRect(m_closeRectangle, OfficeAccent::darkColor(accent()));
    else if (m_stateMaximize == ButtonPress)
        painter.fillRect(m_maximizeRectangle, OfficeAccent::darkColor(accent()));
    else if (m_stateMinimize == ButtonPress)
        painter.fillRect(m_minimizeRectangle, OfficeAccent::darkColor(accent()));

    // Window button icons
    if (OffHasNotFlag(m_flagsWindow, NoCloseButton))
    {
        painter.drawPixmap(centerRectangle(m_imageClose, m_closeRectangle), m_imageClose);
    }
    if (OffHasNotFlag(m_flagsWindow, NoMinimizeButton))
    {
        painter.drawPixmap(centerRectangle(m_imageMinimize, m_minimizeRectangle), m_imageMinimize);
    }
    if (OffHasNotFlag(m_flagsWindow, NoMaximizeButton))
    {
        if (isMaximized())
        {
            painter.drawPixmap(centerRectangle(m_imageRestore, m_maximizeRectangle), m_imageRestore);
        }
        else
        {
            painter.drawPixmap(centerRectangle(m_imageMaximize, m_maximizeRectangle), m_imageMaximize);
        }
    }
}

void OfficeWindow::resizeEvent(QResizeEvent* event)
{
    // Does not generate a drop shadow if resizing or currently being in
    // maximized window mode.
    if (m_stateWindow != StateResize && !isMaximized())
    {
        generateDropShadow();
    }

    updateButtonRectangles();
    updateResizeRectangles();
    updateVisibleTitle();
    updateResizeWidgets();

    QWidget::resizeEvent(event);
}

void OfficeWindow::mouseMoveEvent(QMouseEvent* event)
{
    const QPoint pos = event->pos();

    // Performs several hit-tests. If one of these functions returns true,
    // the title bar will be redrawn.
    if (!mouseMoveDrag(pos))
    {
        if (mouseMoveSpecial(pos) || mouseMoveHitTest(pos))
        {
            repaintTitleBar();
        }
    }

    QWidget::mouseMoveEvent(event);
}

void OfficeWindow::mousePressEvent(QMouseEvent* event)
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
            repaintTitleBar();
        }
    }

    QWidget::mousePressEvent(event);
}

void OfficeWindow::mouseReleaseEvent(QMouseEvent* event)
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
            repaintTitleBar();
        }
    }

    QWidget::mouseReleaseEvent(event);
}

void OfficeWindow::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton &&
        m_dragRectangle.contains(event->pos()) &&
        hasMaximizeButton() &&
        canResize())
    {
        if (isMaximized())
        {
            showNormal();
            updateResizeRectangles();
        }
        else
        {
            showMaximized();
            updateResizeRectangles();
        }

        m_stateMaximize = ButtonNone;

        updateLayoutPadding();
        update();
    }

    QWidget::mouseDoubleClickEvent(event);
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

    QWidget::showEvent(event);
}

void OfficeWindow::leaveEvent(QEvent* event)
{
    if (m_stateWindow == StateDrag)
    {
        // There might be a chance of the mouse pointer leaving the window
        // while we are dragging it.
        move(QCursor::pos() - m_dragPosition);
    }
    else
    {
        m_stateClose    = ButtonNone;
        m_stateMaximize = ButtonNone;
        m_stateMinimize = ButtonNone;

        repaintTitleBar();
    }

    QWidget::leaveEvent(event);
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

void OfficeWindow::repaintTitleBar()
{
    update(m_titleRectangle);
}

void OfficeWindow::updateButtonRectangles()
{
    const QSize& sizeClose = m_imageClose.size();
    const QSize& sizeMaxim = m_imageMaximize.size();
    const QSize& sizeMinim = m_imageMinimize.size();

    // Initial button position.
    int paddingX = (isMaximized()) ? c_windowButtonX : c_iconPosX;
    int paddingY = (isMaximized()) ? c_windowButtonY : c_iconPosY;
    int initialX = width() - sizeClose.width() - paddingX;
    int initialY = paddingY;

    // Close button rectangle.
    if (OffHasNotFlag(m_flagsWindow, NoCloseButton))
    {
        m_closeRectangle.setRect(
            initialX - 10,
            initialY - 8,
            sizeClose.width()  + 20,
            sizeClose.height() + 16
            );

        initialX -= sizeMaxim.width() + 20;
    }

    // Maximize button rectangle.
    if (OffHasNotFlag(m_flagsWindow, NoMaximizeButton))
    {
        m_maximizeRectangle.setRect(
            initialX - 10,
            initialY - 8,
            sizeMaxim.width()  + 20,
            sizeMaxim.height() + 16
            );

        initialX -= sizeMinim.width() + 20;
    }

    // Minimize button rectangle.
    if (OffHasNotFlag(m_flagsWindow, NoMinimizeButton))
    {
        m_minimizeRectangle.setRect(
            initialX - 10,
            initialY - 8,
            sizeMinim.width()  + 20,
            sizeMinim.height() + 16
            );
    }
}

void OfficeWindow::updateResizeRectangles()
{
    int padding = (isMaximized()) ? 0 : c_shadowPadding;
    int totalWidth =
        m_closeRectangle.width()    +
        m_maximizeRectangle.width() +
        m_minimizeRectangle.width();

    int dragWidth =
        width()     -
        padding * 2 -
        totalWidth  -
        m_windowLabelMenu->width() -
        m_windowQuickMenu->width();


    // Resize areas
    m_resizeTopLeft->setGeometry(0, 0, 10, 10);
    m_resizeTopRight->setGeometry(width() - 10, 0, 10, 10);
    m_resizeBottomRight->setGeometry(width() - 10, height() - 10, 10, 10);
    m_resizeBottomLeft->setGeometry(0, height() - 10, 10, 10);
    m_resizeTop->setGeometry(10, 0, width() - 20, 10);
    m_resizeRight->setGeometry(width() - 10, 10, 10, height() - 20);
    m_resizeBottom->setGeometry(10, height() - 10, width() - 20, 10);
    m_resizeLeft->setGeometry(0, 10, 10, height() - 20);

    // Rectangles
    m_dragRectangle.setRect(
        padding + m_windowQuickMenu->width(),
        padding,
        dragWidth,
        c_titleHeight
        );

    m_windowLabelMenu->move(
        m_dragRectangle.x() +
        m_dragRectangle.width(),
        padding
        );

    m_windowQuickMenu->move(
        padding + 1,
        padding + 1
        );

    m_clientRectangle.setRect(
        padding,
        padding,
        width()  - padding * 2,
        height() - padding * 2
        );

    m_titleRectangle.setRect(
        padding,
        padding,
        width() - padding * 2,
        c_titleHeight
        );
}

void OfficeWindow::updateVisibleTitle()
{
    QString title = windowTitle();
    QFontMetrics metrics(font());

    int currentWidth = metrics.width(title);
    int estimatedWidth = m_dragRectangle.width() -
            c_titlePaddingX * 2 -
            c_shadowPadding -
            currentWidth;

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
    else if (windowTitle().length() != title.length())
    {
        title.remove(title.length() - 2, 2).append("...");
    }

    m_visibleTitle = title;
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
            // Disable drop shadow in maximize mode.
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

QRect OfficeWindow::centerRectangle(const QPixmap& pm, const QRect& rc)
{
    int dx = (rc.width()  - pm.width())  / 2;
    int dy = (rc.height() - pm.height()) / 2;

    return QRect(rc.x() + dx, rc.y() + dy, pm.width(), pm.height());
}

bool OfficeWindow::mouseMoveDrag(const QPoint& pos)
{
    if (m_stateWindow == StateDrag)
    {
        auto globalPos = mapToGlobal(pos);
        if (isMaximized())
        {
            m_stateMaximize = ButtonNone;
            m_stateWindow = StateNone;

            // The window is about to be restored. In order to avoid that all
            // the titlebar's contents are invisible for a split second, we
            // recalculate all the necessary things beforehand.
            updateLayoutPadding();
            updateResizeRectangles();

            showNormal();
        }
        else
        {
            move(globalPos - m_dragPosition);
            updateGeometry();
        }

        return true;
    }

    return false;
}

bool OfficeWindow::mouseMoveSpecial(const QPoint& pos)
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

bool OfficeWindow::mouseMoveHitTest(const QPoint& pos)
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

        if (OffHasNotFlag(m_flagsWindow, NoCloseButton) &&
            m_closeRectangle.contains(pos))
        {
            m_stateClose = ButtonHover;
            return true;
        }
        else if (OffHasNotFlag(m_flagsWindow, NoMaximizeButton) &&
            m_maximizeRectangle.contains(pos))
        {
            m_stateMaximize = ButtonHover;
            return true;
        }
        else if (OffHasNotFlag(m_flagsWindow, NoMinimizeButton) &&
            m_minimizeRectangle.contains(pos))
        {
            m_stateMinimize = ButtonHover;
            return true;
        }

        return state;
    }

    return false;
}

bool OfficeWindow::mousePressDrag(const QPoint& pos)
{
    // Activates dragging if the dragging rectangle is being pressed and
    // moved later on.
    if (m_dragRectangle.contains(pos))
    {
        m_dragPosition = pos;
        m_stateWindow = StateDrag;

        return true;
    }

    return false;
}

bool OfficeWindow::mousePressHitTest(const QPoint& pos)
{
    bool state = m_stateClose    != ButtonPress &&
                 m_stateMaximize != ButtonPress &&
                 m_stateMinimize != ButtonPress;

    m_stateClose    = ButtonNone;
    m_stateMaximize = ButtonNone;
    m_stateMinimize = ButtonNone;

    if (OffHasNotFlag(m_flagsWindow, NoCloseButton) &&
        m_closeRectangle.contains(pos))
    {
        m_stateClose = ButtonPress;
        return true;
    }
    else if (OffHasNotFlag(m_flagsWindow, NoMaximizeButton) &&
        m_maximizeRectangle.contains(pos))
    {
        m_stateMaximize = ButtonPress;
        return true;
    }
    else if (OffHasNotFlag(m_flagsWindow, NoMinimizeButton) &&
        m_minimizeRectangle.contains(pos))
    {
        m_stateMinimize = ButtonPress;
        return true;
    }

    return state;
}

bool OfficeWindow::mouseReleaseDrag(const QPoint&)
{
    if (m_stateWindow == StateDrag)
    {
        m_stateWindow = StateNone;

        return true;
    }

    return false;
}

bool OfficeWindow::mouseReleaseAction(const QPoint& pos)
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
            close();
        }
        else if (m_stateMaximize == ButtonPress && m_maximizeRectangle.contains(pos))
        {
            // The window is about to be maximized or restored. In order to
            // avoid that all the titlebar's contents are invisible for a split
            // second, we recalculate all the necessary things beforehand.
            updateButtonRectangles();
            updateResizeRectangles();
            updateLayoutPadding();
            updateVisibleTitle();

            if (isMaximized())
            {
                showNormal();
            }
            else
            {
                showMaximized();
            }
        }
        else if (m_stateMinimize == ButtonPress && m_minimizeRectangle.contains(pos))
        {
            updateLayoutPadding();
            showMinimized();
        }

        m_stateClose    = ButtonNone;
        m_stateMaximize = ButtonNone;
        m_stateMinimize = ButtonNone;

        return true;
    }

    return false;
}

bool OfficeWindow::isActive() const
{
    return isActiveWindow() || m_tooltipVisible;
}
