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
#include <QOffice/Widgets/OfficeMenuPanel.hpp>
#include <QOffice/Widgets/OfficeMenuTopItem.hpp>
#include <QOffice/Widgets/Constants/OfficeMenuConstants.hpp>
#include <QOffice/Design/OfficePalette.hpp>

// Qt headers
#include <QPainter>
#include <QTextOption>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGridLayout>


QOFFICE_USING_NAMESPACE


OfficeMenuPanel::OfficeMenuPanel(OfficeMenuTopItem* parent)
    : QWidget(parent)
    , m_ParentItem(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setMouseTracking(true);
}


OfficeMenuPanel::OfficeMenuPanel(const QString& name)
    : OfficeMenuPanel(nullptr)
{
    setText(name);
}


OfficeMenuPanel::~OfficeMenuPanel()
{
}


QSize
OfficeMenuPanel::sizeHint() const
{
    // Calculates the total width of all items.
    int currentX = 0;
    for (auto* item : m_Items)
    {
        currentX += item->sizeHint().width();
        currentX += MENU_ITEM_SPACING;
    }
    if (m_Items.size() != 0)
    {
        currentX += MENU_PANEL_PADDING;
    }

    return QSize(currentX, MENU_PANEL_HEIGHT);
}


OfficeMenuTopItem*
OfficeMenuPanel::parentItem() const
{
    return m_ParentItem;
}


const QString&
OfficeMenuPanel::text() const
{
    return m_Text;
}


const QRect&
OfficeMenuPanel::bounds() const
{
    return m_Bounds;
}


const QList<OfficeMenuItem*>&
OfficeMenuPanel::items() const
{
    return m_Items;
}


void
OfficeMenuPanel::setText(const QString& text)
{
    m_Text = text;
    update();
}


void
OfficeMenuPanel::addItem(OfficeMenuItem* item)
{
    insertItem(m_Items.size(), item);
}


void
OfficeMenuPanel::insertItem(int pos, OfficeMenuItem* item)
{
    if (item != nullptr)
    {
        // Inserts the new item.
        m_Items.insert(pos++, item);
        item->setParent(this);
        item->m_ParentPanel = this;
        recalculateItem(item);
    }
}


void
OfficeMenuPanel::removeItem(int index)
{
    if (index >= 0 || index < m_Items.size())
        removeItem(m_Items[index]);
}


void
OfficeMenuPanel::removeItem(OfficeMenuItem* item)
{
    if (item != nullptr)
    {
        m_Items.removeOne(item);
        delete item;
    }
}


void
OfficeMenuPanel::removeAll()
{
    for (auto* item : m_Items)
        removeItem(item);
}


void
OfficeMenuPanel::paintEvent(QPaintEvent*)
{
    // Gathers all the needed rects/points for rendering.
    QPainter painter(this);
    QRect rectText = m_Bounds.adjusted(0, 0, 0, -4);
    QPoint ptSepa1 = m_Bounds.topRight() + QPoint(0, 4);
    QPoint ptSepa2 = m_Bounds.bottomRight() - QPoint(0, 8);
    QTextOption opText(Qt::AlignHCenter | Qt::AlignBottom);

    // Gathers all the colors needed for rendering.
    const QColor& colorSepar = OfficePalette::get(OfficePalette::MenuSeparator);
    const QColor& colorForeg = OfficePalette::get(OfficePalette::Foreground);

    // Renders the text
    painter.setPen(colorForeg);
    painter.drawText(rectText, m_Text, opText);
    painter.setPen(colorSepar);
    painter.drawLine(ptSepa1, ptSepa2);
}


void
OfficeMenuPanel::recalculateItem(OfficeMenuItem* item)
{
    QRect bounds;
    QSize newSize;

    // Calculates the width of all previous items.
    int currentX = MENU_PANEL_PADDING;
    int pos = m_Items.indexOf(item);
    int itemWidth = item->sizeHint().width();
    for (int i = 0; i < pos && i < m_Items.size(); i++)
        currentX += (m_Items.at(i)->sizeHint().width() + MENU_ITEM_SPACING);

    // Calculates the new bounds for the item.
    bounds.setRect(0, 0, itemWidth, item->heightHint());
    item->m_Bounds = bounds;
    item->m_TightBounds.setRect(0, 0, itemWidth, item->sizeHint().height());
    item->setGeometry(currentX, MENU_PANEL_PADDING,
                      itemWidth, item->heightHint());

    currentX += (itemWidth + MENU_ITEM_SPACING);
    pos++;

    // Increases the X-position of all items after the new item.
    for (int i = pos; i < m_Items.size(); i++)
    {
        auto* item = m_Items[i];
        item->move(item->x() + itemWidth + MENU_ITEM_SPACING, item->y());
        currentX += item->width();
    }

    currentX += MENU_PANEL_PADDING;

    // If the size is different from before, resize panel.
    if ((newSize = QSize(currentX, MENU_PANEL_HEIGHT)) != size())
    {
        resize(newSize);
        m_Bounds.setSize(newSize);

        emit requestResize(this);
    }
}


void
OfficeMenuPanel::recalculateAllItems()
{
    int currentX = (m_Items.size() != 0) ? MENU_PANEL_PADDING : 0;
    for (auto* item : m_Items)
    {
        // Specifies all the new boundaries.
        QSize itemSize = item->sizeHint();
        item->m_Bounds.setRect(0, 0, itemSize.width(), MENU_ITEM_HEIGHT);
        item->m_TightBounds.setRect(0, 0, itemSize.width(), itemSize.height());
        item->setGeometry(currentX, MENU_PANEL_PADDING,
                          itemSize.width(), MENU_ITEM_HEIGHT);

        // Advances the position (+ padding).
        currentX += (itemSize.width() + MENU_ITEM_SPACING);
    }

    currentX += MENU_PANEL_PADDING;
    resize(currentX, MENU_PANEL_HEIGHT);
    m_Bounds.setSize(size());

    emit requestResize(this);
}
