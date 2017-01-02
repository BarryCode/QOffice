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
#include <QOffice/Plugins/Extensions/OfficeMenuEditorDialog.hpp>
#include <QtUiTools>
#include <iostream>


QOFFICE_USING_NAMESPACE


OfficeMenuEditorDialog::OfficeMenuEditorDialog(OfficeMenu* menu, QWidget* parent)
    : QDialog(parent)
    , m_OldMenu(menu)
    , m_NewMenu(new OfficeMenu)
    , m_SelectedTreeItem(nullptr)
    , m_SelectedDropDownItem(nullptr)
    , m_SelectedTextboxDropDownItem(nullptr)
{
    QUiLoader loader;
    QFile file(":/qoffice/editors/menueditor.ui");

    // Loads the form dynamically from our resources.
    file.open(QFile::ReadOnly);
    m_Form = loader.load(&file, this);
    file.close();

    // Adds it to a layout.
    setLayout(new QGridLayout);
    layout()->addWidget(m_Form);

    // Retrieves the tree widget and the list widgets.
    m_Tree = m_Form->findChild<QTreeWidget*>("tvItems");
    m_List = m_Form->findChild<QListWidget*>("lvDDItems");
    m_TbList = m_Form->findChild<QListWidget*>("lvTextboxDropDown");
    m_Stack = m_Form->findChild<QStackedWidget*>("swItems");

    // Connects all the needed signals to slots.
    connect(m_Tree, SIGNAL(itemSelectionChanged()),
            this, SLOT(onTreeViewItemChange()));
    connect(m_Tree, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(showTreeViewContextMenu(QPoint)));
    connect(m_List, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(onDropDownItemChange(QListWidgetItem*)));
    connect(m_TbList, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(onTextboxDropDownItemChange(QListWidgetItem*)));
    connect(m_Form->findChild<QPushButton*>("btnClearItems"),
            SIGNAL(clicked()), this,
            SLOT(clearAllItems()));
    connect(m_Form->findChild<QPushButton*>("btnSaveItems"),
            SIGNAL(clicked()), this,
            SLOT(saveAllItems()));
    connect(m_Form->findChild<QPushButton*>("btnSaveSingleItem"),
            SIGNAL(clicked()), this,
            SLOT(saveCurrentItem()));
    connect(m_Form->findChild<QPushButton*>("btnDDItemEditSave"),
            SIGNAL(clicked()), this,
            SLOT(saveDropDownItem()));
    connect(m_Form->findChild<QPushButton*>("btnTextboxDDEditSave"),
            SIGNAL(clicked()), this,
            SLOT(saveTextboxDropDownItem()));
    connect(m_Form->findChild<QPushButton*>("btnDDDelItem"),
            SIGNAL(clicked()), this,
            SLOT(removeDropDownItem()));
    connect(m_Form->findChild<QPushButton*>("btnDDAddItem"),
            SIGNAL(clicked()), this,
            SLOT(addDropDownItem()));
    connect(m_Form->findChild<QPushButton*>("btnDDItemUp"),
            SIGNAL(clicked()), this,
            SLOT(putDropDownItemUp()));
    connect(m_Form->findChild<QPushButton*>("btnDDItemDown"),
            SIGNAL(clicked()), this,
            SLOT(putDropDownItemDown()));
    connect(m_Form->findChild<QPushButton*>("btnTextboxDDEditDelItem"),
            SIGNAL(clicked()), this,
            SLOT(removeTextboxDropDownItem()));
    connect(m_Form->findChild<QPushButton*>("btnTextboxDDEditAddItem"),
            SIGNAL(clicked()), this,
            SLOT(addTextboxDropDownItem()));
    connect(m_Form->findChild<QPushButton*>("btnTextboxDDEditItemUp"),
            SIGNAL(clicked()), this,
            SLOT(putTextboxDropDownItemUp()));
    connect(m_Form->findChild<QPushButton*>("btnTextboxDDEditItemDown"),
            SIGNAL(clicked()), this,
            SLOT(putTextboxDropDownItemDown()));

}


OfficeMenuEditorDialog::~OfficeMenuEditorDialog()
{
    delete m_NewMenu;
}


QSize
OfficeMenuEditorDialog::sizeHint() const
{
    return m_Form->size();
}


void
OfficeMenuEditorDialog::clearAllItems()
{
    //m_NewMenu->clearItems();
}


void
OfficeMenuEditorDialog::saveAllItems()
{
    if (QDesignerFormWindowInterface *formWindow
      = QDesignerFormWindowInterface::findFormWindow(m_OldMenu))
    {
        //formWindow->cursor()->setProperty("ItemXml", m_NewMenu->itemXml());
    }

    accept();
}


void
OfficeMenuEditorDialog::addTopMenuItem()
{
}


void
OfficeMenuEditorDialog::addPanel()
{
}


void
OfficeMenuEditorDialog::addItem(QAction* item)
{
    if (item != nullptr)
    {
        if (item->data().toInt() == 0)
        {
            // Add top-menu-item to menu

            QTreeWidgetItem* item = new QTreeWidgetItem;
            item->setText(0, tr("New top item"));
            m_Tree->addTopLevelItem(item);
            item->setData(0, Qt::UserRole, 0);
            item->setSelected(true);
            m_SelectedTreeItem = item;
        }
        else if (item->data().toInt() == 1)
        {
            // Retrieve top-menu-item from user data
            // Add panel

            QTreeWidgetItem* item = new QTreeWidgetItem;
            item->setText(0, tr("New panel"));
            item->setData(0, Qt::UserRole, 1);
            m_SelectedTreeItem->addChild(item);
        }
        else if (item->data().toInt() == 2)
        {
            // Add top-menu-item

            bool ok;
            auto text = QInputDialog::getItem(
                        this, tr("Choose item type"), tr("Type: "),
                        { "Button", "Separator", "DropDownButton",
                          "Textbox", "ItemGroup" }, 0, false, &ok);

            if (ok)
            {
                QTreeWidgetItem* item = new QTreeWidgetItem;
                item->setText(0, "New " + text);
                item->setData(0, Qt::UserRole, 2);
                item->setData(1, Qt::UserRole, text);
                m_SelectedTreeItem->addChild(item);
            }
        }
        else if (item->data().toInt() == 3)
        {
            // Remove selected item.

            delete m_SelectedTreeItem;
            m_SelectedTreeItem = nullptr;
        }
    }
}


void
OfficeMenuEditorDialog::removePanel()
{
}


void
OfficeMenuEditorDialog::removeTopMenuItem()
{
}


void
OfficeMenuEditorDialog::removeItem()
{
}


void
OfficeMenuEditorDialog::saveCurrentItem()
{
}


void
OfficeMenuEditorDialog::addDropDownItem()
{
}


void
OfficeMenuEditorDialog::addTextboxDropDownItem()
{
}


void
OfficeMenuEditorDialog::removeDropDownItem()
{
}


void
OfficeMenuEditorDialog::removeTextboxDropDownItem()
{
}


void
OfficeMenuEditorDialog::putDropDownItemUp()
{
}


void
OfficeMenuEditorDialog::putTextboxDropDownItemUp()
{
}


void
OfficeMenuEditorDialog::putDropDownItemDown()
{
}


void
OfficeMenuEditorDialog::putTextboxDropDownItemDown()
{
}


void
OfficeMenuEditorDialog::saveDropDownItem()
{
}


void
OfficeMenuEditorDialog::saveTextboxDropDownItem()
{
}


void
OfficeMenuEditorDialog::onTreeViewItemChange()
{
    if (m_Tree->selectedItems().isEmpty())
        m_SelectedTreeItem = nullptr;
    else
        m_SelectedTreeItem = m_Tree->selectedItems()[0];


    if (m_SelectedTreeItem != nullptr)
    {
        int data = m_SelectedTreeItem->data(0, Qt::UserRole).toInt();
        if (data == 0)
        {
            m_Stack->setCurrentIndex(6);
        }
        else if (data == 1)
        {
            m_Stack->setCurrentIndex(5);
        }
        else if (data == 2)
        {
            QString type = m_SelectedTreeItem->data(1, Qt::UserRole).toString();
            if (type == "Button")
            {
                m_Stack->setCurrentIndex(0);
            }
            else if (type == "Separator")
            {
                m_Stack->setCurrentIndex(2);
            }
            else if (type == "DropDownButton")
            {
                m_Stack->setCurrentIndex(1);
            }
            else if (type == "Textbox")
            {
                m_Stack->setCurrentIndex(3);
            }
            else
            {
                m_Stack->setCurrentIndex(4);
            }
        }
    }
}


void
OfficeMenuEditorDialog::onDropDownItemChange(QListWidgetItem* item)
{
    m_SelectedDropDownItem = item;
}


void
OfficeMenuEditorDialog::onTextboxDropDownItemChange(QListWidgetItem* item)
{
    m_SelectedTextboxDropDownItem = item;
}


void
OfficeMenuEditorDialog::showTreeViewContextMenu(QPoint pos)
{
    QMenu* contextMenu = new QMenu(this);
           m_CurrentMenuActions.clear();

    int itemType = determineTreeWidgetItemType();
    if (m_Tree->itemAt(pos) == nullptr)
        itemType = 0;
    if (itemType == 0)
    {
        m_CurrentMenuActions.append(contextMenu->addAction("Add top menu item"));
        m_CurrentMenuActions.last()->setData(0);
    }
    if (itemType == 1)
    {
        m_CurrentMenuActions.append(contextMenu->addAction("Add panel"));
        m_CurrentMenuActions.last()->setData(1);
    }
    if (itemType == 2)
    {
        m_CurrentMenuActions.append(contextMenu->addAction("Add menu item"));
        m_CurrentMenuActions.last()->setData(2);
    }
    if (itemType != 0)
    {
        m_CurrentMenuActions.append(contextMenu->addAction("Remove item"));
        m_CurrentMenuActions.last()->setData(3);
    }

    connect(contextMenu,
            SIGNAL(triggered(QAction*)),
            this, SLOT(addItem(QAction*)));

    contextMenu->popup(m_Tree->mapToGlobal(pos));
}


int
OfficeMenuEditorDialog::determineTreeWidgetItemType()
{
    if (m_SelectedTreeItem == nullptr)
        return 0; // top-menu-item
    if (m_SelectedTreeItem->parent() == nullptr)
        return 1; // panel
    if (m_SelectedTreeItem->parent()->parent() == nullptr)
        return 2; // menu item

    return 3;
}
