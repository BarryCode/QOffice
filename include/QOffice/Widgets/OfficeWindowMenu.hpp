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

class OfficeTooltip;
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
    /// Adds a label item to the window menu.
    ///
    /// \param[in] id The unique identifier of the menu item.
    /// \param[in] text The displayed text of the label.
    /// \param[in] tooltip (opt) The tooltip text shown on mouse hover.
    /// \return False if the ID already exists, true otherwise.
    ///
    /// \remarks Also returns false if this menu is not a label menu.
    ///
    ////////////////////////////////////////////////////////////////////////////
    bool addLabelItem(int id, const QString& text, const QString& tooltip = "");

    ////////////////////////////////////////////////////////////////////////////
    /// Adds a quick item to the window menu.
    ///
    /// \param[in] id The unique identifier of the menu item.
    /// \param[in] icon The displayed icon.
    /// \param[in] tooltip (opt) The tooltip text shown on mouse hover.
    /// \return False if the ID already exists, true otherwise.
    ///
    /// \remarks Also returns false if this menu is not a quick menu.
    ///
    ////////////////////////////////////////////////////////////////////////////
    bool addQuickItem(int id, const QPixmap& icon, const QString& tooltip = "");

    ////////////////////////////////////////////////////////////////////////////
    /// Removes the menu item with the given text.
    ///
    /// \param[in] id The unique identifier of the item to remove.
    /// \return True if item removed, false otherwise.
    ///
    ////////////////////////////////////////////////////////////////////////////
    bool removeItem(int id);

signals:

    ////////////////////////////////////////////////////////////////////////////
    /// This signal is emitted once the user clicks a menu item.
    ///
    /// \param[in] id The unique identifier of the clicked item.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void menuItemClicked(int id);

    ////////////////////////////////////////////////////////////////////////////
    /// This signal is emitted once the user requests help while the tooltip of
    /// a menu item is shown.
    ///
    /// \param[in] id The unique identifier of the clicked item.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void helpRequested(int id);

private slots:

    void onItemClicked(priv::WindowItem*);
    void onHelpRequested();
    void onShowTooltip(priv::WindowItem*);
    void onHideTooltip(priv::WindowItem*);
    void showTooltip();
    void hideTooltip();
    bool addItem(
        const int id,
        const QString& t,
        const QPixmap& i = QPixmap(),
        const QString& tt = QString()
        );

private:

    ////////////////////////////////////////////////////////////////////////////
    // Members
    //
    ////////////////////////////////////////////////////////////////////////////
    Type                     m_type;
    QList<priv::WindowItem*> m_items;
    priv::WindowItem*        m_trigger;
    OfficeWindow*            m_parent;
    QLayout*                 m_layout;
    OfficeTooltip*           m_tooltip;
    QTimer*                  m_timer;

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
