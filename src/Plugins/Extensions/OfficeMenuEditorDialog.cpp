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


QOFFICE_USING_NAMESPACE


OfficeMenuEditorDialog::OfficeMenuEditorDialog(OfficeMenu* menu, QWidget* parent)
    : QDialog(parent)
    , m_OldMenu(menu)
    , m_NewMenu(new OfficeMenu)
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

    // Connects all the needed signals to slots.
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
