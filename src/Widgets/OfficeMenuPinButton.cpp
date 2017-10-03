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

#include <QOffice/Design/OfficePalette.hpp>
#include <QOffice/Widgets/OfficeMenu.hpp>
#include <QOffice/Widgets/OfficeMenuHeader.hpp>
#include <QOffice/Widgets/OfficeMenuPinButton.hpp>
#include <QOffice/Widgets/OfficeTooltip.hpp>

#include <QPainter>
#include <QMouseEvent>

OffAnonymous(bool g_isSticky = false)

priv::PinButton::PinButton(OfficeMenuHeader* parent)
    : QWidget(parent)
    , m_parent(parent)
    , m_tooltip(new OfficeTooltip)
    , m_imgSticky(":/qoffice/images/widgets/menu_sticky.png")
    , m_imgCollapse(":/qoffice/images/widgets/menu_collapse.png")
    , m_isHovered(false)
    , m_isPressed(false)
{
    setFixedSize(30, 16);
    setMinimumSize(30, 16);
    setMaximumSize(30, 16);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    m_tooltip->setWaitPeriod(1000);
    m_tooltip->setHelpEnabled(false);
}

QSize priv::PinButton::sizeHint() const
{
    return QSize(30, 16);
}

void priv::PinButton::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    if (m_isPressed)
    {
        painter.fillRect(rect(), OfficePalette::color(OfficePalette::MenuItemPress));
    }
    else if (m_isHovered)
    {
        painter.fillRect(rect(), OfficePalette::color(OfficePalette::MenuItemHover));
    }

    if (!g_isSticky)
    {
        painter.drawPixmap(QPoint(), m_imgSticky);
    }
    else
    {
        painter.drawPixmap(QPoint(), m_imgCollapse);
    }
}

void priv::PinButton::enterEvent(QEvent* event)
{
    m_tooltip->hide();
    m_tooltip->move(QCursor::pos());
    m_tooltip->resize(200, 100);

    if (!g_isSticky)
    {
        m_tooltip->setTitle("Pin");
        m_tooltip->setText("Pins the ribbon bar and makes it permanent.");
    }
    else
    {
        m_tooltip->setTitle("Collapse");
        m_tooltip->setText("Unpins the ribbon bar and makes it temporary.");
    }

    // Hack: Showing the tooltip would steal the focus of the OfficeMenu,
    // causing it to collapse. We temporarily "pin" the menu for that purpose.
    m_parent->menu()->m_isTooltipShown = true;
    m_tooltip->show();
    m_isHovered = true;

    update();

    QWidget::enterEvent(event);
}

void priv::PinButton::leaveEvent(QEvent* event)
{
    m_parent->menu()->m_isTooltipShown = false;
    m_tooltip->hide();
    m_isHovered = false;

    update();

    QWidget::leaveEvent(event);
}

void priv::PinButton::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_isPressed = true;
        update();
    }

    QWidget::mousePressEvent(event);
}

void priv::PinButton::mouseReleaseEvent(QMouseEvent* event)
{
    if (rect().contains(event->pos()) && event->button() == Qt::LeftButton)
    {
        g_isSticky = !g_isSticky;
        m_parent->menu()->setPinned(g_isSticky);
    }

    m_tooltip->hide();
    m_isPressed = false;
    update();

    QWidget::mouseReleaseEvent(event);
}
