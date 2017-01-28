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
#include <QOffice/Widgets/OfficeMenuSubMenu.hpp>
#include <QOffice/Design/OfficeAccents.hpp>
#include <QOffice/Widgets/Constants/OfficeMenuConstants.hpp>

// Qt headers
#include <QPainter>
#include <QResizeEvent>
#include <QtXml/QDomDocument>


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


QString
OfficeMenu::itemXml() const
{
    return m_ItemXml;
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

        // Changes the geometry of the sub-menu.
        itemToExpand->m_SubMenu->resize(
                    width(),
                    itemToExpand->m_SubMenu->height());
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
        QRect bounds;

        // Calculates the width of all previous items.
        int currentX = 0;
        int itemWidth = fontMetrics().width(item->text());
        for (int i = 0; i < pos && i < m_Items.size(); i++)
            currentX += (m_Items.at(i)->bounds().width() + 2);

        // Calculates the estimated bounds.
        bounds.setRect(0, 0, itemWidth + MENU_ITEM_PADDING, MENU_COLLAPSED_HEIGHT);

        // Integrates the item into the menu.
        item->m_Bounds = bounds;
        item->setGeometry(bounds.adjusted(currentX, 0, currentX, 0));
        item->m_ParentMenu = this;
        item->setParent(this);
        m_Items.insert(pos++, item);

        // Allocates a sub menu for the menu item.
        item->m_SubMenu->setParent(this);
        item->m_SubMenu->setGeometry(0, MENU_COLLAPSED_HEIGHT,
                               width(), MENU_EXPANDED_HEIGHT -
                                        MENU_COLLAPSED_HEIGHT);

        // Increases the X-position of all items after the new item.
        for (int i = pos; i < m_Items.size(); i++)
        {
            auto* item = m_Items[i];
            item->m_Bounds.setX(item->m_Bounds.x() + bounds.width() + 2);
        }
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


OfficeMenuItem*
OfficeMenu::menuItemById(const QString& identifier)
{
    // If this is the first time this function is called,
    // caches all items and their identifiers.
    if (m_IdMap.isEmpty())
    {
        for (auto* topItem : m_Items)
            for (auto* panel : topItem->panels())
                for (auto* item : panel->items())
                    m_IdMap.insert(item->identifier(), item);
    }

    // Retrieves the item from the identifier-map.
    return m_IdMap[identifier];
}


OfficeMenuItem*
OfficeMenu::operator[](const QString& identifier)
{
    return menuItemById(identifier);
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
        // Resizes every item with the menu.
        if (item->isSelected())
            item->m_SubMenu->resize(width(), item->m_SubMenu->height());
    }
}


void
OfficeMenu::showEvent(QShowEvent*)
{
    for (auto* item : m_Items)
        item->recalculateAllPanels();
}


bool
OfficeMenu::loadFromXml(const QString& xml)
{
    QDomDocument doc;
    QDomElement topNode;
    doc.setContent(xml);
    topNode = doc.elementsByTagName("officeMenu").at(0).toElement();

    // Reads all the top menu items.
    auto topNodeElems = topNode.elementsByTagName("topItem");
    for (int i = 0; i < topNodeElems.size(); i++)
    {
        OfficeMenuTopItem* topItem = new OfficeMenuTopItem;
        QDomElement nodeElem = topNodeElems.at(i).toElement();
        QString name = nodeElem.attribute("text");

        // Sets the displayed text of the menu item.
        topItem->setText(name);

        // Parses all the panels.
        auto panelNodeElems = nodeElem.elementsByTagName("panel");
        for (int j = 0; j < panelNodeElems.size(); j++)
        {
            OfficeMenuPanel* panel = new OfficeMenuPanel;
            QDomElement panelElem = panelNodeElems.at(j).toElement();
            QString name = panelElem.attribute("text");

            // Sets the displayed text of the panel.
            panel->setText(name);

            // Parses all the items.
            auto itemNodeElems = panelElem.elementsByTagName("item");
            for (int k = 0; k < itemNodeElems.size(); k++)
            {
                OfficeMenuItem* item;
                QDomElement itemElem = itemNodeElems.at(k).toElement();

                if ((item = xmlGetItem(&itemElem)) == nullptr)
                    return false;

                panel->addItem(item);
            }

            topItem->addPanel(panel);
        }

        addItem(topItem);
    }

    // Everything parsed successfully.
    m_ItemXml = xml;
    return true;
}


OfficeMenuItem*
OfficeMenu::xmlGetItem(QDomElement* itemElem)
{
    QString type = itemElem->attribute("type");

    // Determines the item type.
    if (type == "Button")
    {
        // Parses the button item.
        auto i = new OfficeMenuButtonItem;
        auto children = itemElem->childNodes();
        for (int j = 0; j < children.size(); j++)
        {
            auto btnNode = children.at(j);
            if (btnNode.nodeName() == "text")
                i->setText(btnNode.firstChild().nodeValue());
            else if (btnNode.nodeName() == "icon")
                i->setIcon(QPixmap(btnNode.firstChild().nodeValue()));
            else if (btnNode.nodeName() == "identifier")
                i->setIdentifier(btnNode.firstChild().nodeValue());
            else if (btnNode.nodeName() == "tooltip")
                i->setTooltipText(btnNode.firstChild().nodeValue());
            else
            {
                qDebug() << "OfficeMenu: Unknown node name "
                         << btnNode.nodeName()
                         << " for OfficeMenuButtonItem.";
            }
        }

        return i;
    }
    else if (type == "Separator")
    {
        // Parses the separator item.
        return new OfficeMenuSeparatorItem;
    }
    else if (type == "DropDownButton")
    {
        auto i = new OfficeMenuDropDownButtonItem;
        auto children = itemElem->childNodes();
        for (int j = 0; j < children.size(); j++)
        {
            auto ddNode = children.at(j);
            if (ddNode.nodeName() == "text")
                i->setText(ddNode.firstChild().nodeValue());
            else if (ddNode.nodeName() == "icon")
                i->setIcon(QPixmap(ddNode.firstChild().nodeValue()));
            else if (ddNode.nodeName() == "identifier")
                i->setIdentifier(ddNode.firstChild().nodeValue());
            else if (ddNode.nodeName() == "dditem")
                i->addItem(ddNode.firstChild().nodeValue());
            else
            {
                qDebug() << "OfficeMenu: Unknown node name "
                         << ddNode.nodeName()
                         << " for OfficeMenuDropDownButtonItem.";
            }
        }

        return i;
    }
    else if (type == "Textbox")
    {
        /*auto i = new OfficeMenuTextboxItem;
        auto children = itemElem->childNodes();
        for (int j = 0; j < children.size(); j++)
        {
            auto tbNode = children.at(j);
            if (tbNode.nodeName() == "initialText")
                i->setText(tbNode.nodeValue());
            else if (tbNode.nodeName() == "label")
                i->setLabel(tbNode.nodeValue());
            else if (tbNode.nodeName() == "dditem")
                i->addItem(tbNode.nodeValue());
            else
            {
                qDebug() << "OfficeMenu: Unknown node name "
                         << tbNode.nodeName()
                         << " for OfficeMenuTextboxItem.";
            }
        }

        return i;*/
        return nullptr;
    }
    else if (type == "ItemGroup")
    {
        /*auto i = new OfficeMenuItemGroup;
        auto children = itemElem->childNodes();
        for (int j = 0; j < children.size(); j++)
        {
            OfficeMenuItem *item;
            QDomElement igElem = children.at(j).toElement();

            if ((item = xmlGetItem(&igElem)) != nullptr)
                i->addItem(item);
        }

        return i;*/
        return nullptr;
    }
    else
    {
        qDebug() << "OfficeMenu: Type "
                 << type
                 << " is not a valid item type!";

        return nullptr;
    }
}


OfficeMenuEventArgs::OfficeMenuEventArgs(const QString &iid,
                                         const QString &data,
                                         Type type)
    : m_ItemId(iid)
    , m_Data(data)
    , m_Type(type)
{
}


const QString&
OfficeMenuEventArgs::itemId() const
{
    return m_ItemId;
}


const QString&
OfficeMenuEventArgs::data() const
{
    return m_Data;
}


OfficeMenuEventArgs::Type
OfficeMenuEventArgs::type() const
{
    return m_Type;
}
