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


#ifndef QOFFICE_OFFICEMENUTASKMENU_HPP
#define QOFFICE_OFFICEMENUTASKMENU_HPP


// QOffice headers
#include <QOffice/Config.hpp>
#include <QOffice/Widgets/OfficeMenu.hpp>

// Qt headers
#include <QDesignerTaskMenuExtension>
#include <QExtensionFactory>
#include <QExtensionManager>
#include <QAction>


QOFFICE_BEGIN_NAMESPACE


/**
 * Adds one menu item to the widget context menu.
 *
 * @class OfficeMenuTaskMenu
 * @author Nicolas Kogler
 * @date January 1st, 2016
 *
 */
class OfficeMenuTaskMenu : public QObject, public QDesignerTaskMenuExtension
{
public:

    /**
     * Initializes a new instance of OfficeMenuTaskMenu.
     *
     * @param menu The OfficeMenu containing the context menu.
     * @param parent The parent of this class.
     *
     */
    explicit OfficeMenuTaskMenu(OfficeMenu* menu, QObject* parent);


    /**
     * Returns the preferred context menu item.
     *
     * @returns the preffered context menu item.
     *
     */
    QAction* preferredEditAction() const override;

    /**
     * Returns a list of the new menu items.
     *
     * @returns the new menu items.
     *
     */
    QList<QAction*> taskActions() const override;


private slots:

    void editItems();


private:

    // Members
    QAction*    m_EditItemsAction;
    OfficeMenu* m_OfficeMenu;

    // Metadata
    Q_OBJECT
    Q_INTERFACES(QDesignerTaskMenuExtension)
};


/**
 * Adds one menu item to the widget context menu.
 *
 * @class OfficeMenuTaskMenu
 * @author Nicolas Kogler
 * @date January 1st, 2016
 *
 */
class OfficeMenuTaskMenuFactory : public QExtensionFactory
{
public:

    /**
     * Initializes a new instance of OfficeMenuTaskMenuFactory.
     *
     * @param parent The parent extension manager.
     *
     */
    explicit OfficeMenuTaskMenuFactory(QExtensionManager* parent = nullptr);


protected:

    /**
     * Instantiates the extension.
     *
     * @returns a pointer to the extension.
     */
    QObject* createExtension(QObject*, const QString&, QObject*) const override;


private:

    // Metadata
    Q_OBJECT
};


QOFFICE_END_NAMESPACE


#endif // QOFFICE_OFFICEMENUTASKMENU_HPP
