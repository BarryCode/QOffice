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
#include <QOffice/Design/OfficeAccents.hpp>
#include <QOffice/Widgets/Constants/OfficeMenuConstants.hpp>

// Qt headers
#include <QPainter>
#include <QResizeEvent>


QOFFICE_USING_NAMESPACE


OfficeMenu::OfficeMenu(QWidget* parent)
    : QWidget(parent)
    , m_IsExpanded(false)
{
    m_Accent = IOfficeWidget::Blue;
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
}


OfficeMenu::~OfficeMenu()
{
}


QSize
OfficeMenu::sizeHint() const
{
    return QSize(-1, (m_IsExpanded)
                 ? MENU_EXPANDED_HEIGHT
                 : MENU_COLLAPSED_HEIGHT);
}


void
OfficeMenu::expand(OfficeMenuTopItem* itemToExpand)
{
    if (itemToExpand != nullptr)
    {
        for (auto* item : m_Items)
        {
            // Collapses any other opened items.
            if (item != itemToExpand)
                item->collapse(false);
        }

        // Changes the height of the menu.
        resize(width(), MENU_EXPANDED_HEIGHT);
        setMinimumHeight(MENU_EXPANDED_HEIGHT);
    }
}


void
OfficeMenu::collapse()
{
    resize(width(), MENU_COLLAPSED_HEIGHT);
    setMinimumHeight(MENU_COLLAPSED_HEIGHT);
}


IOfficeWidget::Accent
OfficeMenu::accent() const
{
    return m_Accent;
}


void
OfficeMenu::setAccent(Accent accent)
{
    m_Accent = accent;
    update();
}


void
OfficeMenu::addItem(OfficeMenuTopItem* item)
{
    insertItem(m_Items.size(), item);
}


void
OfficeMenu::insertItem(int pos, OfficeMenuTopItem* item)
{
    if (item != nullptr)
    {
        int currentX = 0;
        for (auto* item : m_Items)
            currentX += (item->bounds().width() + 2);

        // Calculates the estimated bounds.
        int wdText = fontMetrics().width(item->text());
        QRect bounds(currentX, 0, wdText + MENU_ITEM_PADDING, MENU_COLLAPSED_HEIGHT);

        // Integrates the item into the menu.
        item->m_Bounds = bounds;
        item->setGeometry(bounds);
        item->m_ParentMenu = this;
        item->setParent(this);
        m_Items.insert(pos, item);
    }
}


void
OfficeMenu::removeItem(int index)
{
    if (index >= 0 && index < m_Items.size())
        removeItem(m_Items[index]);
}


void
OfficeMenu::removeItem(OfficeMenuTopItem* item)
{
    if (item != nullptr)
    {
        m_Items.removeOne(item);
        delete item;
    }
}


void
OfficeMenu::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QRect rectBackg(0, 0, width(), MENU_COLLAPSED_HEIGHT);

    painter.fillRect(rectBackg, OfficeAccents::get(accent()));
}


void
OfficeMenu::resizeEvent(QResizeEvent*)
{
    for (auto* item : m_Items)
    {
        if (item->isSelected())
            item->resize(width(), item->height());
    }
}
