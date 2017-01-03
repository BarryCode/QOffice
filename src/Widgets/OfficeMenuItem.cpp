/*
 *  QOffice: Office UI framework for Qt
 *  Copyright (C) 2016-2017 Nicolas Kogler
 *
 *  This file is part of QOffice.
 *
 *  QOffice is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  QOffice is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with QOffice. If not, see <http://www.gnu.org/licenses/>.
 *
 */


// QOffice headers
#include <QOffice/Widgets/OfficeMenuItem.hpp>
#include <QOffice/Widgets/OfficeMenuPanel.hpp>
#include <QOffice/Design/OfficePalette.hpp>

// Qt headers
#include <QPainter>
#include <QTextOption>
#include <QMouseEvent>


QOFFICE_USING_NAMESPACE


OfficeMenuItem::OfficeMenuItem(OfficeMenuPanel *parent)
    : QWidget(parent)
    , m_Timer(new QTimer(this))
    , m_ParentPanel(parent)
    , m_Tooltip(new OfficeTooltip(this))
{
    setAttribute(Qt::WA_TranslucentBackground);
    setMouseTracking(true);

    m_Timer->setInterval(1000);
    connect(m_Timer, SIGNAL(timeout()), this, SLOT(showTooltip()));
    connect(m_Tooltip, SIGNAL(helpRequested()), this, SLOT(onHelpRequested()));
}


OfficeMenuItem::~OfficeMenuItem()
{
}


QSize
OfficeMenuItem::sizeHint() const
{
    return m_Bounds.size();
}


const QRect&
OfficeMenuItem::bounds() const
{
    return m_Bounds;
}

const QString&
OfficeMenuItem::identifier() const
{
    return m_Identifier;
}


const QString&
OfficeMenuItem::text() const
{
    return m_Text;
}


const QString&
OfficeMenuItem::tooltipText() const
{
    return m_TooltipText;
}


void
OfficeMenuItem::setIdentifier(const QString& id)
{
    m_Identifier = id;
}


void
OfficeMenuItem::setText(const QString& text)
{
    m_Text = text;
}


void
OfficeMenuItem::setTooltipText(const QString& text)
{
    m_TooltipText = text;
}


void
OfficeMenuItem::enterEvent(QEvent*)
{
    m_Timer->start();
}


void
OfficeMenuItem::leaveEvent(QEvent*)
{
    m_Timer->stop();
    m_Tooltip->hide();
}


void
OfficeMenuItem::onHelpRequested()
{
    emit helpRequested();
}


void
OfficeMenuItem::showTooltip()
{
    QPoint pos = mapToGlobal(QCursor::pos());
    QSize size(200, 200);

    m_Tooltip->setGeometry(QRect(pos, size));
    m_Tooltip->setHeading(m_Text);
    m_Tooltip->setText(m_TooltipText);
    m_Tooltip->show();
    m_Timer->stop();
}


OfficeMenuButtonItem::OfficeMenuButtonItem(OfficeMenuPanel* parent)
    : OfficeMenuItem(parent)
    , m_State(MenuButtonState::None)
{
}


OfficeMenuButtonItem::~OfficeMenuButtonItem()
{
}


const QPixmap&
OfficeMenuButtonItem::icon() const
{
    return m_Icon;
}


void
OfficeMenuButtonItem::setIcon(const QPixmap& pm)
{
    m_Icon = pm;
}


void
OfficeMenuButtonItem::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QTextOption opText(Qt::AlignVCenter | Qt::AlignBottom);

    // Gathers all the needed colors for rendering.
    const QColor& colorHover = OfficePalette::get(OfficePalette::MenuItemHover);
    const QColor& colorPress = OfficePalette::get(OfficePalette::MenuItemPress);
    const QColor& colorTextE = OfficePalette::get(OfficePalette::Foreground);
    const QColor& colorTextD = OfficePalette::get(OfficePalette::DisabledText);

    // Renders the background, if either hovered or pressed.
    if (m_State == MenuButtonState::Hovered)
        painter.fillRect(m_Bounds, colorHover);
    else if (m_State == MenuButtonState::Pressed)
        painter.fillRect(m_Bounds, colorPress);

    // Renders the text.
    if (isEnabled())
        painter.setPen(colorTextE);
    else
        painter.setPen(colorTextD);

    painter.drawText(m_TightBounds, m_Text, opText);

    // Renders the icon.
    QRect iconRect((m_Bounds.width() - m_Icon.width()) / 2,
                   (m_Bounds.height() - m_Icon.height()) / 2,
                    m_Icon.width(),
                    m_Icon.height());

    painter.drawPixmap(iconRect, m_Icon);
}


void
OfficeMenuButtonItem::enterEvent(QEvent* event)
{
    if (isEnabled())
    {
        m_State = MenuButtonState::Hovered;
        update();

        OfficeMenuItem::enterEvent(event);
    }
}


void
OfficeMenuButtonItem::leaveEvent(QEvent* event)
{
    if (isEnabled())
    {
        m_State = MenuButtonState::None;
        update();

        OfficeMenuItem::leaveEvent(event);
    }
}


void
OfficeMenuButtonItem::mousePressEvent(QMouseEvent* event)
{
    if (isEnabled() && event->button() == Qt::LeftButton)
    {
        m_State = MenuButtonState::Pressed;
        update();
    }
}


void
OfficeMenuButtonItem::mouseReleaseEvent(QMouseEvent* event)
{
    if (isEnabled() && event->button() == Qt::LeftButton)
    {
        if (m_Bounds.contains(event->pos()))
            m_State = MenuButtonState::Hovered;
        else
            m_State = MenuButtonState::None;

        update();
    }
}
