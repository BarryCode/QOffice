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
#include <QOffice/Plugins/Extensions/OfficeMenuTaskMenu.hpp>
#include <QOffice/Plugins/Extensions/OfficeMenuEditorDialog.hpp>


QOFFICE_USING_NAMESPACE


OfficeMenuTaskMenu::OfficeMenuTaskMenu(OfficeMenu* menu, QObject* parent)
    : QObject(parent)
    , m_EditItemsAction(new QAction(tr("Edit items..."), this))
    , m_OfficeMenu(menu)
{
    connect(m_EditItemsAction, SIGNAL(triggered()), this, SLOT(editItems()));
}


void
OfficeMenuTaskMenu::editItems()
{
    OfficeMenuEditorDialog dialog(m_OfficeMenu);
    dialog.exec();
}


QAction*
OfficeMenuTaskMenu::preferredEditAction() const
{
    return m_EditItemsAction;
}


QList<QAction*>
OfficeMenuTaskMenu::taskActions() const
{
    return QList<QAction*>({ m_EditItemsAction });
}


OfficeMenuTaskMenuFactory::OfficeMenuTaskMenuFactory(QExtensionManager* parent)
    : QExtensionFactory(parent)
{
}


QObject* OfficeMenuTaskMenuFactory::createExtension(
        QObject* obj,
        const QString& iid,
        QObject* parent) const
{
    if (iid != Q_TYPEID(QDesignerTaskMenuExtension))
        return nullptr;

    if (OfficeMenu* menu = qobject_cast<OfficeMenu*>(obj))
        return new OfficeMenuTaskMenu(menu, parent);

    return nullptr;
}
