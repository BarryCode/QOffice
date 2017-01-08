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


#ifndef QOFFICE_OFFICEMENUSUBMENU_HPP
#define QOFFICE_OFFICEMENUSUBMENU_HPP


// QOffice headers
#include <QOffice/Config.hpp>

// Qt headers
#include <QWidget>


QOFFICE_BEGIN_NAMESPACE


class OfficeMenu;


/**
 * Defines the menu bar underneath the top menu items.
 *
 * @class OfficeMenuSubMenu
 * @author Nicolas Kogler
 * @date January 3rd, 2016
 *
 */
class QOFFICE_EXPORT OfficeMenuSubMenu : public QWidget
{
public:

    /**
     * Initializes a new instance of OfficeMenuSubMenu
     *
     * @param parent The parent office menu.
     *
     */
    OfficeMenuSubMenu(OfficeMenu* parent = nullptr);

    /**
     * Frees all resources used by OfficeMenuSubMenu.
     *
     */
    virtual ~OfficeMenuSubMenu();


protected:

    /**
     * Renders the sub-menu.
     *
     * @param event Holds nothing we need.
     *
     */
    virtual void paintEvent(QPaintEvent* event) override;


private:

    // Metadata
    Q_OBJECT
};


QOFFICE_END_NAMESPACE


#endif // QOFFICE_OFFICEMENUSUBMENU_HPP
