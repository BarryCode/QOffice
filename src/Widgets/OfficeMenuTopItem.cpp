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
#include <QOffice/Widgets/OfficeMenuTopItem.hpp>
#include <QOffice/Widgets/OfficeMenu.hpp>
#include <QOffice/Design/OfficeAccents.hpp>
#include <QOffice/Design/OfficePalette.hpp>

// Qt headers
#include <QPainter>
#include <QtEvents>


QOFFICE_USING_NAMESPACE


OfficeMenuTopItem::OfficeMenuTopItem(OfficeMenu* parent)
    : QWidget(parent)
    , m_ParentMenu(parent)
    , m_IsSelected(false)
    , m_IsHovered(false)
    , m_DirtyRegion(TopItemDirtyRegion::Text |
                    TopItemDirtyRegion::Bar)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setMouseTracking(true);
}


OfficeMenuTopItem::~OfficeMenuTopItem()
{
}


bool
OfficeMenuTopItem::isSelected() const
{
    return m_IsSelected;
}


const QString&
OfficeMenuTopItem::text() const
{
    return m_Text;
}


const QRect&
OfficeMenuTopItem::bounds() const
{
    return m_Bounds;
}


const QList<OfficeMenuPanel*>&
OfficeMenuTopItem::panels() const
{
    return m_Panels;
}


OfficeMenuPanel*
OfficeMenuTopItem::panelAt(int index) const
{
    if (index < 0 || index >= m_Panels.size())
        return nullptr;

    return m_Panels[index];
}


OfficeMenuPanel*
OfficeMenuTopItem::panelAt(const QPoint& pos) const
{
    // Determines which panel is visually located at the given pos.
    for (auto* panel : m_Panels)
    {
        if (panel->bounds().contains(pos))
            return panel;
    }

    return nullptr;
}


void
OfficeMenuTopItem::select()
{
    if (m_IsSelected)
        return;

    //m_ParentMenu->expand();
    m_IsSelected = true;
    m_DirtyRegions |= TopItemDirtyRegion::Bar;
    update();

    for (auto* panel : m_Panels)
        panel->show();

    emit itemExpanded();
}


void
OfficeMenuTopItem::collapse()
{
    if (!m_IsSelected)
        return;

    //m_ParentMenu->collapse();
    m_IsSelected = false;
    m_DirtyRegions &= ~TopItemDirtyRegion::Bar;

    for (auto* panel : m_Panels)
        panel->hide();

    emit itemCollapsed();
}


void
OfficeMenuTopItem::setText(const QString& text)
{
    m_Text = text;
    m_DirtyRegions |= TopItemDirtyRegion::Text;
    update();
}


void
OfficeMenuTopItem::addPanel(OfficeMenuPanel* panel)
{
    insertPanel(m_Panels.size(), panel);
}


void
OfficeMenuTopItem::addPanel(const QString& name)
{
    insertPanel(m_Panels.size(), name);
}


void
OfficeMenuTopItem::insertPanel(int pos, OfficeMenuPanel* panel)
{
    if (panel != nullptr)
    {
        m_Panels.insert(pos, panel);
        panel->setParent(this);
        panel->update();
    }
}


void
OfficeMenuTopItem::insertPanel(int pos, const QString& name)
{
    insertPanel(pos, new OfficeMenuPanel(name));
}


void
OfficeMenuTopItem::removePanel(int index)
{
    if (index >= 0 || index < m_Panels.size())
        removePanel(m_Panels[index]);
}


void
OfficeMenuTopItem::removePanel(OfficeMenuPanel* panel)
{
    m_Panels.removeOne(panel);
    panel->hide();
    delete panel;
}


void
OfficeMenuTopItem::removeAll()
{
    for (auto* panel : m_Panels)
        removePanel(panel);
}


void
OfficeMenuTopItem::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    // Gets the background and accent color.
    const QColor& colorAccnt = OfficeAccents::get(m_ParentMenu->accent());
    const QColor& colorBackg = OfficePalette::get(OfficePalette::Background);

    // If the text is dirty, redraw the tab.
    if ((m_DirtyRegions & TopItemDirtyRegion::Text) != 0)
    {
        if (m_IsSelected)
        {
            painter.fillRect(m_Bounds, colorBackg);
            painter.setPen(colorAccnt);
        }
        else if (m_IsHovered)
        {
            painter.fillRect(m_Bounds, OfficeAccents::lighter(colorAccnt));
            painter.setPen(colorBackg);
        }
        else
        {
            painter.fillRect(m_Bounds, colorAccnt);
            painter.setPen(colorBackg);
        }

        painter.drawText(m_Bounds, m_Text, QTextOption(Qt::AlignCenter));
        m_DirtyRegions &= ~TopItemDirtyRegion::Text;
    }

    // If the actual menu bar is dirty, redraw it.
    if ((m_DirtyRegions & TopItemDirtyRegion::Bar) != 0 && m_IsSelected)
    {
        const QColor& colorSepar = OfficePalette::get(OfficePalette::MenuSeparator);
        const QPoint pLineS = rect().bottomLeft();
        const QPoint pLineE = rect().bottomRight();
        const QRect rectBar = rect().adjusted(
                    0,  m_Bounds.bottom(),
                    0, -m_Bounds.bottom() - 1);

        painter.fillRect(rectBar, colorBackg);
        painter.setPen(colorSepar);
        painter.drawLine(pLineS, pLineE);
        m_DirtyRegions &= ~TopItemDirtyRegion::Bar;
    }
}


void
OfficeMenuTopItem::mouseMoveEvent(QMouseEvent* event)
{
    bool oldState = m_IsHovered;
    if (!m_IsSelected && m_Bounds.contains(event->pos()))
        m_IsHovered = true;
    else
        m_IsHovered = false;

    if (oldState != m_IsHovered)
    {
        m_DirtyRegions |= TopItemDirtyRegion::Text;
        update();
    }
}


void
OfficeMenuTopItem::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (m_Bounds.contains(event->pos()))
        {
            if (!m_IsSelected)
                select();
            else
                collapse();
        }
    }
}
