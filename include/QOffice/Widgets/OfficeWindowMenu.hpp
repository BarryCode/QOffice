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

namespace priv { class Titlebar; }

////////////////////////////////////////////////////////////////////////////////
/// \class OfficeWindowMenu
/// \ingroup Widget
///
/// \brief Defines a menu on the window title bar.
/// \author Nicolas Kogler
/// \date September 27, 2017
///
/// QOffice has two types of window menus: The LabelMenu and the QuickMenu. The
/// label menu is located on the right-hand side of the window and simply shows
/// a clickable text (hand cursor on hover). The quick menu is located on the
/// left-hand side of the window and shows an image, but no text (normal cursor
/// on hover).
///
/// \code
/// const int idItem1 = 0;
/// const int idItem2 = 0;
///
/// m_labelMenu = new OfficeWindowMenu(window, OfficeWindowMenu::LabelMenu);
/// m_labelMenu->addLabelItem(idItem1, "Item1", "This item does this.");
/// m_labelMenu->addLabelItem(idItem2, "Item2", "This item does that.");
/// m_labelMenu->connect(m_labelMenu, &OfficeWindowMenu::itemClicked, this, [...]);
/// \endcode
///
/// The OfficeWindowMenu::itemClicked signal will be emitted whenever the user
/// clicks on a window menu item. The id of the item will be provided:
///
/// \code
/// void itemClickedSlot(int id)
/// {
///     if (id == idItem1)
///     {
///         // do something
///     }
///     else if (id == idItem2)
///     {
///         // do something
///     }
/// }
/// \endcode
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

    OffDeclareDtor(OfficeWindowMenu)
    OffDisableCopy(OfficeWindowMenu)
    OffDisableMove(OfficeWindowMenu)

    ////////////////////////////////////////////////////////////////////////////
    /// Initializes a new instance of the OfficeWindowMenu while the given
    /// \p parent is specified as owner of this widget.
    ///
    /// \param[in] parent The window titlebar that owns this menu.
    /// \param[in] type The window type.
    ///
    ////////////////////////////////////////////////////////////////////////////
    OfficeWindowMenu(priv::Titlebar* parent, Type type);

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
    void itemClicked(int id);

    ////////////////////////////////////////////////////////////////////////////
    /// This signal is emitted once the user requests help while the tooltip of
    /// a menu item is shown.
    ///
    /// \param[in] id The unique identifier of the clicked item.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void helpRequested(int id);

protected:

    virtual void leaveEvent(QEvent*) override;

private slots:

    void onItemClicked(priv::WindowItem*);
    void onHelpRequested();
    void onShowTooltip(priv::WindowItem*);
    void onHideTooltip(priv::WindowItem*);
    bool addItem(
        const int id,
        const QString& t,
        const QPixmap& i = QPixmap(),
        const QString& tt = QString()
        );

private:

    Type                     m_type;
    QList<priv::WindowItem*> m_items;
    OfficeWindow*            m_parent;
    OfficeTooltip*           m_tooltip;

    friend class priv::WindowItem;
    friend class OfficeWindow;

    Q_OBJECT
};

#endif
