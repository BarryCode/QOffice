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
#include <QOffice/Widgets/Dialogs/OfficeWindowMenu.hpp>
#include <QOffice/Widgets/Dialogs/OfficeWindow.hpp>
#include <QOffice/Design/OfficeAccents.hpp>

// Qt headers
#include <QPainter>
#include <QMouseEvent>
#include <QToolTip>


QOFFICE_USING_NAMESPACE


OfficeWindowMenu::OfficeWindowMenu(OfficeWindow* parent)
    : QWidget(parent)
    , m_HoveredItem(nullptr)
    , m_Parent(parent)
    , m_Tooltip(new OfficeTooltip())
    , m_Timer(new QTimer(this))
{
    m_Timer->setInterval(1000);
    connect(m_Timer, SIGNAL(timeout()), this, SLOT(showTooltip()));
    connect(m_Tooltip, SIGNAL(helpRequested()), this, SLOT(onHelpRequested()));
    setMouseTracking(true);
}


OfficeWindowMenu::~OfficeWindowMenu()
{
    for (auto* item : m_Items)
        delete item;

    m_Tooltip->close();
    delete m_Tooltip;
}


const QList<OfficeWindowMenuItem*>&
OfficeWindowMenu::items() const
{
    return m_Items;
}


void
OfficeWindowMenu::setItems(const QList<OfficeWindowMenuItem*>& items)
{
    for (auto* item : items)
        item->m_Parent = this;

    m_Items = items;
    update();
}


QSize
OfficeWindowMenu::sizeHint() const
{
    // Calculates the size of every item.
    int currentPos = 0;
    for (auto* item : m_Items)
    {
        item->m_Bounds.setX(currentPos);
        item->m_Bounds.setY(0);
        item->m_Bounds.setWidth(item->icon().width() + 8);
        item->m_Bounds.setHeight(24);
        currentPos += item->m_Bounds.width();
    }

    return QSize(currentPos, 24);
}


void
OfficeWindowMenu::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    const QColor& colorAccnt = OfficeAccents::get(m_Parent->accent());

    // Renders every icon in enabled or disabled state.
    for (auto* item : m_Items)
    {
        QRect bounds = item->m_Bounds;
        QRect iconRect(bounds.x() + 4, bounds.y() + 4, 16, 16);

        if (!m_Parent->isActive())
            painter.setOpacity(0.5);
        if (item->m_State == WinButtonState::Hovered)
            painter.fillRect(bounds, OfficeAccents::lighter(colorAccnt));
        else if (item->m_State == WinButtonState::Pressed)
            painter.fillRect(bounds, OfficeAccents::darker(colorAccnt));

        if (item->isEnabled() && m_Parent->isActive())
            painter.setOpacity(1.0);
        else
            painter.setOpacity(0.5);

        painter.drawPixmap(iconRect, item->icon());
        painter.setOpacity(1.0);
    }
}


void
OfficeWindowMenu::mouseMoveEvent(QMouseEvent* event)
{
    QPoint pos = event->pos();

    // Determines which of the menu items is hovered.
    for (auto* item : m_Items)
    {
        if (item->isEnabled() && item->m_State != WinButtonState::Pressed)
        {
            if (item->m_Bounds.contains(pos))
            {
                item->m_State = WinButtonState::Hovered;
                m_HoveredItem = item;
                m_Timer->start();
                update();
                break;
            }
            else
            {
                item->m_State = WinButtonState::None;
                m_HoveredItem = nullptr;
                m_Tooltip->hide();
                m_Timer->stop();
            }
        }
    }
}


void
OfficeWindowMenu::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        // Determines whether one of the items is hovered.
        // If it is, it will be advanced to the pressed state.
        for (auto* item : m_Items)
        {
            if (item->isEnabled() && item->m_State == WinButtonState::Hovered)
            {
                item->m_State = WinButtonState::Pressed;
                m_Timer->stop();
                update();
                break; // no other item can be hovered.
            }
        }
    }
}


void
OfficeWindowMenu::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        // The pressed item is now either hovered or nothing.
        int index = 0;
        for (auto* item : m_Items)
        {
            if (item->isEnabled() && item->m_State == WinButtonState::Pressed)
            {
                if (item->m_Bounds.contains(event->pos()))
                {
                    item->m_State = WinButtonState::Hovered;
                    m_Tooltip->hide();
                    emit menuItemClicked(index);
                }
                else
                {
                    item->m_State = WinButtonState::None;
                }

                update();
                break; // no other item can be pressed.
            }

            index++;
        }
    }
}


void
OfficeWindowMenu::leaveEvent(QEvent*)
{
    for (auto* item : m_Items)
        item->m_State = WinButtonState::None;

    if (!m_Tooltip->geometry().contains(QCursor::pos()))
         m_Tooltip->beginHideTooltip();

    m_Timer->stop();
    update();
}


void
OfficeWindowMenu::showTooltip()
{
    QPoint pos = mapToGlobal(m_HoveredItem->m_Bounds.bottomLeft());
    QSize size(200, 200);

    m_Tooltip->setGeometry(QRect(pos, size));
    m_Tooltip->setText(m_HoveredItem->tooltip());
    m_Tooltip->show();
    m_Timer->stop();
}


void
OfficeWindowMenu::onHelpRequested()
{
    emit helpRequested(m_Items.indexOf(m_HoveredItem));
}


OfficeWindowMenuItem::OfficeWindowMenuItem()
    : m_IsEnabled(true)
    , m_Parent(nullptr)
    , m_State(WinButtonState::None)
{
}


const QPixmap&
OfficeWindowMenuItem::icon() const
{
    return m_Icon;
}


const QString&
OfficeWindowMenuItem::tooltip() const
{
    return m_Tooltip;
}


bool
OfficeWindowMenuItem::isEnabled() const
{
    return m_IsEnabled;
}


void
OfficeWindowMenuItem::setIcon(const QPixmap& img)
{
    m_Icon = img;

    if (m_Parent != nullptr)
        m_Parent->update();
}


void
OfficeWindowMenuItem::setTooltip(const QString& str)
{
    m_Tooltip = str;
}


void
OfficeWindowMenuItem::setEnabled(bool enabled)
{
    m_IsEnabled = enabled;

    if (m_Parent != nullptr)
        m_Parent->update();
}
