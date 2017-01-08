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
#include <QOffice/Widgets/OfficeMenu.hpp>
#include <QOffice/Widgets/OfficeMenuItem.hpp>
#include <QOffice/Widgets/OfficeMenuPanel.hpp>
#include <QOffice/Widgets/Constants/OfficeMenuConstants.hpp>
#include <QOffice/Design/OfficePalette.hpp>
#include <QOffice/Design/OfficeImaging.hpp>

// Qt headers
#include <QPainter>
#include <QTextOption>
#include <QMouseEvent>


QOFFICE_USING_NAMESPACE


OfficeMenuItem::OfficeMenuItem(OfficeMenuPanel *parent)
    : QWidget(parent)
    , m_Timer(new QTimer(this))
    , m_Tooltip(new OfficeTooltip(this))
    , m_ParentPanel(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setToolTipDuration(3000);
    setMouseTracking(true);

    m_Timer->setInterval(1000);
    connect(m_Timer, SIGNAL(timeout()), this, SLOT(showTooltip()));
    connect(m_Tooltip, SIGNAL(helpRequested()), this, SLOT(onHelpRequested()));
}


OfficeMenuItem::~OfficeMenuItem()
{
}


OfficeMenu*
OfficeMenuItem::parentMenu()
{
    return m_ParentPanel->parentItem()->parentMenu();
}


OfficeMenuPanel*
OfficeMenuItem::parentPanel()
{
    return m_ParentPanel;
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


const QString&
OfficeMenuItem::tooltipHelpText() const
{
    return m_TooltipHelpText;
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
    update();

    emit requestResize(this);
}


void
OfficeMenuItem::setTooltipText(const QString& text)
{
    m_TooltipText = text;
}


void
OfficeMenuItem::setTooltipHelpText(const QString& text)
{
    m_TooltipHelpText = text;
}


void
OfficeMenuItem::enterEvent(QEvent*)
{
    if (!m_TooltipText.isEmpty())
         m_Timer->start();
}


void
OfficeMenuItem::leaveEvent(QEvent*)
{
    if (!m_TooltipHelpText.isEmpty() &&
        !m_Tooltip->geometry().contains(QCursor::pos()))
    {
        m_Timer->stop();
        m_Tooltip->hide();
    }
}


void
OfficeMenuItem::onHelpRequested()
{
    emit helpRequested();
}


void
OfficeMenuItem::showTooltip()
{
    QPoint pos = QCursor::pos();
    QSize size(200, 200);

    m_Tooltip->setGeometry(QRect(pos, size));
    m_Tooltip->setHeading(m_Text);
    m_Tooltip->setText(m_TooltipText);
    m_Tooltip->setHelpText(m_TooltipHelpText);
    m_Tooltip->setDisplayDuration(toolTipDuration());
    m_Tooltip->show();
    m_Timer->stop();
}


OfficeMenuButtonItem::OfficeMenuButtonItem(OfficeMenuPanel* parent)
    : OfficeMenuItem(parent)
    , m_State(MenuButtonState::None)
    , m_ParentGroup(nullptr)
{
}


OfficeMenuButtonItem::~OfficeMenuButtonItem()
{
}


QSize
OfficeMenuButtonItem::sizeHint() const
{
    // Calculates the estimated size of the item.
    if (m_ParentGroup == nullptr)
    {
        int width = 0, height = 0;
        if (!m_Icon.isNull())
        {
            width = m_Icon.width();
            height += m_Icon.height();
            height += MENU_BUTTON_IMAGE_PAD;
        }

        // Calculates the width and height of the text, if any.
        if (!m_Text.isEmpty())
        {
            width = qMax(width, fontMetrics().boundingRect(m_Text).width());
            width += MENU_BUTTON_PADDING;
            height += fontMetrics().tightBoundingRect(m_Text).height();
        }

        return QSize(width, height);
    }
    else
    {
        int width = MENU_BUTTON_GROUP_PADDING, height = MENU_BUTTON_GROUP_HEIGHT;
        if (!m_Icon.isNull())
        {
            width += 16;
            width += MENU_BUTTON_GROUP_IMAGE_PAD;
        }

        // Calculates the width of the text.
        if (!m_Text.isEmpty())
        {
            width += fontMetrics().boundingRect(m_Text).width();
            width += MENU_BUTTON_GROUP_PADDING;
        }

        return QSize(width, height);
    }
}


int
OfficeMenuButtonItem::heightHint() const
{
    return MENU_ITEM_HEIGHT;
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
    m_DisabledIcon = OfficeImaging::toGrayscale(m_Icon);
    update();

    emit requestResize(this);
}


void
OfficeMenuButtonItem::setGroup(OfficeMenuItemGroup* group)
{
    m_ParentGroup = group;
    //setParent(group);
}


void
OfficeMenuButtonItem::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QTextOption opText((m_ParentGroup)
                ? Qt::AlignVCenter | Qt::AlignRight
                : Qt::AlignHCenter | Qt::AlignBottom);

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
    QRect iconRect;
    if (!m_ParentGroup)
    {
        iconRect.setRect((m_Bounds.width() - m_Icon.width()) / 2,
                          0,
                          m_Icon.width(),
                          m_Icon.height());
    }
    else
    {
        iconRect.setRect(MENU_BUTTON_GROUP_IMAGE_PAD, 0, 16, 16);
    }

    if (isEnabled())
        painter.drawPixmap(iconRect, m_Icon);
    else
        painter.drawPixmap(iconRect, m_DisabledIcon);
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
        m_Tooltip->hide();
        m_Timer->stop();
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


        OfficeMenuEventArgs eventArgs(
                    identifier(),
                    QString(),
                    OfficeMenuEventArgs::ButtonClick);

        emit parentMenu()->itemEvent(&eventArgs);
        emit clicked();

        update();
    }
}


OfficeMenuSeparatorItem::OfficeMenuSeparatorItem(OfficeMenuPanel* parent)
    : OfficeMenuItem(parent)
{

}

OfficeMenuSeparatorItem::~OfficeMenuSeparatorItem()
{
}


QSize
OfficeMenuSeparatorItem::sizeHint() const
{
    return QSize(1, MENU_ITEM_HEIGHT);
}


int
OfficeMenuSeparatorItem::heightHint() const
{
    return MENU_ITEM_HEIGHT;
}


void
OfficeMenuSeparatorItem::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.fillRect(rect(), OfficePalette::get(OfficePalette::MenuSeparator));
}


OfficeMenuDropDownButtonItem::
OfficeMenuDropDownButtonItem(OfficeMenuPanel* parent)
    : OfficeMenuItem(parent)
    , m_DropDown(new OfficeDropDown)
{
    m_DropDown->setParent(this);
}
