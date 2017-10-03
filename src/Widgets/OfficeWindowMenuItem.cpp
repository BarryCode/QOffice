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
#include <QOffice/Design/OfficePalette.hpp>
#include <QOffice/Widgets/OfficeWindowMenu.hpp>
#include <QOffice/Widgets/OfficeWindowMenuItem.hpp>
#include <QOffice/Widgets/Dialogs/OfficeWindow.hpp>

#include <QPainter>
#include <QtEvents>

QRect centerRectangle(const QPixmap& pm, const QRect& rc)
{
    int dx = (rc.width()  - pm.width())  / 2;
    int dy = (rc.height() - pm.height()) / 2;

    return QRect(rc.x() + dx, rc.y() + dy, pm.width(), pm.height());
}

priv::WindowItem::WindowItem(
    OfficeWindowMenu* parent,
    int type,
    int id,
    const QString& text,
    const QPixmap& image,
    const QString& tooltip
    )
    : QWidget(parent)
    , m_type(type)
    , m_id(id)
    , m_isHovered(false)
    , m_isPressed(false)
    , m_text(text)
    , m_image(image)
    , m_tooltip(tooltip)
    , m_parent(parent)
{
    if (type == OfficeWindowMenu::LabelMenu)
    {
        // The labels on the LabelMenu are links with underlined text. In order
        // to make them look like "Hyperlinks", change the cursor to a hand.
        setCursor(Qt::PointingHandCursor);
    }

    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    setMouseTracking(true);
}

int priv::WindowItem::id() const
{
    return m_id;
}

const QString& priv::WindowItem::text() const
{
    return m_text;
}

const QPixmap& priv::WindowItem::image() const
{
    return m_image;
}

const QString& priv::WindowItem::tooltipText() const
{
    return m_tooltip;
}

void priv::WindowItem::setText(const QString& text)
{
    m_text = text;
}

void priv::WindowItem::setImage(const QPixmap& img)
{
    m_image = img;
}

void priv::WindowItem::setTooltipText(const QString& text)
{
    m_tooltip = text;
}

QSize priv::WindowItem::sizeHint() const
{
    if (m_type == OfficeWindowMenu::LabelMenu)
    {
        return fontMetrics().size(0, m_text);
    }
    else if (m_type == OfficeWindowMenu::QuickMenu)
    {
        return QSize(32, 26);
    }

    return QSize();
}

void priv::WindowItem::enterEvent(QEvent* event)
{
    m_isHovered = true;

    emit tooltipShowRequested(this);

    QWidget::enterEvent(event);
}

void priv::WindowItem::leaveEvent(QEvent* event)
{
    m_isHovered = false;

    emit tooltipHideRequested(this);

    QWidget::leaveEvent(event);
}

void priv::WindowItem::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    if (m_type == OfficeWindowMenu::LabelMenu)
    {
        auto currentFont = font();
        if (m_isHovered)
        {
            currentFont.setUnderline(true);
        }

        if (!m_parent->m_parent->isActive())
        {
            // When the window is not active, the titlebar text and the titlebar
            // buttons should not be rendered darker but rather blend into the
            // background.
            painter.setOpacity(0.5);
        }

        painter.setFont(currentFont);
        painter.setPen(OfficePalette::color(OfficePalette::Background));
        painter.drawText(rect(), m_text);
    }
    else if (m_type == OfficeWindowMenu::QuickMenu)
    {
        if (!m_parent->m_parent->isActive())
        {
            painter.setOpacity(0.5);
        }

        auto accent = m_parent->m_parent->accent();
        if (m_isPressed)
        {
            painter.fillRect(rect(), OfficeAccent::darkColor(accent));
        }
        else if (m_isHovered)
        {
            painter.fillRect(rect(), OfficeAccent::lightColor(accent));
        }

        painter.drawPixmap(centerRectangle(m_image, rect()), m_image);
    }
}

void priv::WindowItem::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_isPressed = true;
        update();

        emit clicked(this);
    }

    emit tooltipHideRequested(this);

    QWidget::mousePressEvent(event);
}

void priv::WindowItem::mouseReleaseEvent(QMouseEvent* event)
{
    m_isPressed = false;
    update();

    QWidget::mouseReleaseEvent(event);
}
