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
#include <QOffice/Widgets/OfficeMenuSubMenu.hpp>
#include <QOffice/Widgets/OfficeMenu.hpp>
#include <QOffice/Widgets/Constants/OfficeMenuConstants.hpp>
#include <QOffice/Design/OfficeAccents.hpp>
#include <QOffice/Design/OfficePalette.hpp>

// Qt headers
#include <QPainter>
#include <QtEvents>
#include <QLayout>


QOFFICE_USING_NAMESPACE


OfficeMenuTopItem::OfficeMenuTopItem(OfficeMenu* parent)
    : QWidget(parent)
    , m_ParentMenu(parent)
    , m_IsSelected(false)
    , m_IsHovered(false)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setMouseTracking(true);

    m_SubMenu = new OfficeMenuSubMenu;
    m_SubMenu->hide();
}


OfficeMenuTopItem::~OfficeMenuTopItem()
{
}


QSize
OfficeMenuTopItem::sizeHint() const
{
    return m_Bounds.size();
}


OfficeMenu*
OfficeMenuTopItem::parentMenu() const
{
    return m_ParentMenu;
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

    m_ParentMenu->expand(this);
    m_SubMenu->show();
    m_IsSelected = true;
    update();

    emit itemExpanded();
}


void
OfficeMenuTopItem::collapse(bool collapseMenu)
{
    if (!m_IsSelected)
        return;

    if (collapseMenu)
        m_ParentMenu->collapse();

    m_SubMenu->hide();
    m_IsSelected = false;
    update();

    emit itemCollapsed();
}


void
OfficeMenuTopItem::setText(const QString& text)
{
    m_Text = text;
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
        panel->m_ParentItem = this;  // internal parent
        panel->setParent(m_SubMenu); // visual parent

        // Makes sure that the menu is informed about panel resize events.
        connect(panel, SIGNAL(requestResize(OfficeMenuPanel*)),
                this,  SLOT(recalculatePanel(OfficeMenuPanel*)));
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

    // Renders the text.
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
        update();
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


void
OfficeMenuTopItem::leaveEvent(QEvent*)
{
    if (m_IsHovered)
    {
        m_IsHovered = false;
        update();
    }
}


void
OfficeMenuTopItem::recalculatePanel(OfficeMenuPanel* panel)
{
    QRect bounds;

    // Calculates the width of all previous items.
    int currentX = 0;
    int pos = m_Panels.indexOf(panel);
    int panelWidth = panel->sizeHint().width();
    for (int i = 0; i < pos && i < m_Panels.size(); i++)
        currentX += m_Panels.at(i)->sizeHint().width();

    // Calculates the new bounds for the item.
    bounds.setRect(0, 0, panelWidth, MENU_PANEL_HEIGHT - 4);
    panel->m_Bounds = bounds;
    panel->setGeometry(currentX, 0,
                      panelWidth, MENU_PANEL_HEIGHT);

    currentX += panelWidth;

    // Increases the X-position of all items after the new item.
    for (int i = pos; i < m_Panels.size(); i++)
    {
        auto* panel = m_Panels[i];
        panel->move(panel->x() + panelWidth, panel->y());
        //currentX += panel->width(); may need this for overflow arrow later
    }
}


void
OfficeMenuTopItem::recalculateAllPanels()
{
    int currentX = 0;
    for (auto* panel : m_Panels)
    {
        panel->recalculateAllItems();

        // Specifies all the new boundaries.
        QSize panelSize = panel->sizeHint();
        panel->m_Bounds.setRect(0, 0, panelSize.width(), MENU_PANEL_HEIGHT - 4);
        panel->setGeometry(currentX, MENU_PANEL_PADDING,
                          panelSize.width(), MENU_PANEL_HEIGHT);

        // Advances the position.
        currentX += panelSize.width();
    }
}

