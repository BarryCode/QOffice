////////////////////////////////////////////////////////////////////////////////
//
// QOffice - The office framework for Qt
// Copyright (C) 2016-2018 Nicolas Kogler
//
// This file is part of the Widget module.
//
// QOffice is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// QOffice is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with QOffice. If not, see <http://www.gnu.org/licenses/>.
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef QOFFICE_WIDGETS_OFFICEWINDOWMENU_HPP
#define QOFFICE_WIDGETS_OFFICEWINDOWMENU_HPP

#include <QOffice/Widgets/OfficeWindowMenuItem.hpp>

class OfficeWindow;

////////////////////////////////////////////////////////////////////////////////
/// \class OfficeWindowMenu
/// \brief Defines a menu on the window title bar.
/// \author Nicolas Kogler (nicolas.kogler@hotmail.com)
/// \date September 27, 2017
///
////////////////////////////////////////////////////////////////////////////////
class QOFFICE_WIDGET_API OfficeWindowMenu : public QWidget
{
public:

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Defines the menu types for the window menu.
    /// \enum Type
    ///
    ////////////////////////////////////////////////////////////////////////////
    enum Type
    {
        LabelMenu,
        QuickMenu
    };

    OffDefaultDtor(OfficeWindowMenu)
    OffDisableCopy(OfficeWindowMenu)
    OffDisableMove(OfficeWindowMenu)

    ////////////////////////////////////////////////////////////////////////////
    /// Initializes a new instance of the OfficeWindowMenu while the given
    /// \p parent is specified as owner of this widget.
    ///
    /// \param[in] parent The window that owns this menu.
    /// \param[in] type The window type.
    ///
    ////////////////////////////////////////////////////////////////////////////
    OfficeWindowMenu(OfficeWindow* parent, Type type);

    ////////////////////////////////////////////////////////////////////////////
    /// Adds a new menu item with the given parameters.
    ///
    /// \param[in] text The displayed text of the menu item.
    /// \param[in] img The image next to the text (optional).
    /// \param[in] tooltip The tooltip text shown on mouse hover (optional).
    /// \return False if the text already exists, true otherwise.
    ///
    ////////////////////////////////////////////////////////////////////////////
    bool addItem(
        const QString& text,
        const QPixmap& img = QPixmap(),
        const QString& tooltip = QString()
        );

    ////////////////////////////////////////////////////////////////////////////
    /// Removes the menu item with the given text.
    ///
    /// \param[in] text The text of the menu item to remove.
    /// \return True if item removed, false otherwise.
    ///
    ////////////////////////////////////////////////////////////////////////////
    bool removeItem(const QString& text);

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the desired size of this window menu.
    ///
    /// \return The requested width and height, in pixels.
    ///
    ////////////////////////////////////////////////////////////////////////////
    //QSize sizeHint() const;

signals:

    ////////////////////////////////////////////////////////////////////////////
    /// This signal is emitted once the user clicks a menu item.
    ///
    /// \param[in] text The text of the clicked item.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void menuItemClicked(QString text);

    ////////////////////////////////////////////////////////////////////////////
    /// This signal is emitted once the user requests help while the tooltip of
    /// a menu item is shown.
    ///
    /// \param[in] text The text of the item which's tooltip requested help.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void helpRequested(QString text);

private slots:

    void onItemClicked(priv::WindowItem*);
    void onHelpRequested(priv::WindowItem*);

private:

    ////////////////////////////////////////////////////////////////////////////
    // Members
    //
    ////////////////////////////////////////////////////////////////////////////
    Type                     m_type;
    QList<priv::WindowItem*> m_items;
    OfficeWindow*            m_parent;
    QLayout*                 m_layout;
    //OfficeTooltip* m_tooltip;
    //QTimer* m_timer;

    friend class priv::WindowItem;

    Q_OBJECT
};

#endif

////////////////////////////////////////////////////////////////////////////////
/// \class OfficeWindowMenu
/// \ingroup Widget
///
/// QOffice has two types of window menus: The LabelMenu and the QuickMenu. The
/// label menu is located on the right-hand side of the window and simply shows
/// a clickable text (hand cursor on hover). The quick menu is located on the
/// left-hand side of the window and shows an image, but no text (normal cursor
/// on hover).
///
/// \code
/// <example_code>
/// \endcode
///
////////////////////////////////////////////////////////////////////////////////
