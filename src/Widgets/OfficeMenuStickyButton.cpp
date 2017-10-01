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

#include <QOffice/Design/OfficePalette.hpp>
#include <QOffice/Widgets/OfficeMenu.hpp>
#include <QOffice/Widgets/OfficeMenuHeader.hpp>
#include <QOffice/Widgets/OfficeMenuStickyButton.hpp>
#include <QOffice/Widgets/OfficeTooltip.hpp>

#include <QPainter>
#include <QMouseEvent>

OffAnonymous(bool g_isSticky = false)

priv::StickyButton::StickyButton(OfficeMenuHeader* parent)
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
}

QSize priv::StickyButton::sizeHint() const
{
    return QSize(30, 16);
}

void priv::StickyButton::paintEvent(QPaintEvent*)
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

void priv::StickyButton::enterEvent(QEvent* event)
{
    m_isHovered = true;
    update();

    QWidget::enterEvent(event);
}

void priv::StickyButton::leaveEvent(QEvent* event)
{
    m_isHovered = false;
    update();

    QWidget::leaveEvent(event);
}

void priv::StickyButton::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_isPressed = true;
        update();
    }

    QWidget::mousePressEvent(event);
}

void priv::StickyButton::mouseReleaseEvent(QMouseEvent* event)
{
    if (rect().contains(event->pos()) && event->button() == Qt::LeftButton)
    {
        g_isSticky = !g_isSticky;
        m_parent->menu()->setPinned(g_isSticky);
    }

    m_isPressed = false;
    update();

    QWidget::mouseReleaseEvent(event);
}
