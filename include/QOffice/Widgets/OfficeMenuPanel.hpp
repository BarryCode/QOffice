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
#ifndef QOFFICE_WIDGET_OFFICEMENUPANEL_HPP
#define QOFFICE_WIDGET_OFFICEMENUPANEL_HPP

#include <QOffice/Config.hpp>
#include <QWidget>

class OfficeMenuHeader;
class OfficeMenuItem;
class QGridLayout;

////////////////////////////////////////////////////////////////////////////////
/// \class OfficeMenuPanel
/// \brief Defines a panel that contains items of various kinds.
/// \author Nicolas Kogler (nicolas.kogler@hotmail.com)
/// \date September 30, 2017
///
////////////////////////////////////////////////////////////////////////////////
class QOFFICE_WIDGET_API OfficeMenuPanel : public QWidget
{
public:

    OffDefaultDtor(OfficeMenuPanel)
    OffDisableCopy(OfficeMenuPanel)
    OffDisableMove(OfficeMenuPanel)

    ////////////////////////////////////////////////////////////////////////////
    /// Initializes a new instance of OfficeMenuPanel with the given \p panelBar
    /// being the owner of this panel. The \p header is not the physical parent
    /// of the panel, but the logical.
    ///
    /// \param[in] panelBar The panel bar this panel belongs to.
    /// \param[in] header The header this panel belongs to logically.
    ///
    ////////////////////////////////////////////////////////////////////////////
    OfficeMenuPanel(QWidget* panelBar, OfficeMenuHeader* header);

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the unique identifier of this object.
    ///
    /// \return The unique identifier.
    ///
    ////////////////////////////////////////////////////////////////////////////
    int id() const;

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the logical parent header of this panel.
    ///
    /// \return The logical parent of this panel.
    ///
    ////////////////////////////////////////////////////////////////////////////
    OfficeMenuHeader* header() const;

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the displayed panel text.
    ///
    /// \return The displayed panel text.
    ///
    ////////////////////////////////////////////////////////////////////////////
    const QString& text() const;

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the item with the specified \p id.
    ///
    /// \param[in] id The unique identifier of the item.
    /// \return The item corresponding to the given \p id.
    ///
    /// \remarks Yields nullptr if id is invalid.
    ///
    ////////////////////////////////////////////////////////////////////////////
    OfficeMenuItem* itemById(int id) const;

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the item with the specified \p id. Is equivalent to calling
    /// OfficeMenuPanel::itemById(id).
    ///
    /// \param[in] id The unique identifier of the item.
    /// \return The item corresponding to the given \p id.
    ///
    /// \remarks Yields nullptr if id is invalid.
    ///
    ////////////////////////////////////////////////////////////////////////////
    OfficeMenuItem* operator [](int id) const;

    ////////////////////////////////////////////////////////////////////////////
    /// Specifies the unique identifier of this object.
    ///
    /// \param[in] id The new unique identifier.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void setId(int id);

    ////////////////////////////////////////////////////////////////////////////
    /// Specifies the displayed panel text.
    ///
    /// \param[in] text The new displayed panel text.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void setText(const QString& text);

    ////////////////////////////////////////////////////////////////////////////
    /// Inserts a new menu item into the panel.
    ///
    /// \param id     The unique identifier of the item to insert.
    /// \param item   The new item to be inserted into the panel.
    /// \param row    The layout row to insert item to.
    /// \param column The layout column to insert item to.
    /// \return True if successfully inserted, false otherwise.
    ///
    /// \remarks Yields false if the id already exists.
    ///
    ////////////////////////////////////////////////////////////////////////////
    bool insertItem(int id, OfficeMenuItem* item, int row, int column);

    ////////////////////////////////////////////////////////////////////////////
    /// Inserts a new menu item into the panel.
    ///
    /// \param id         The unique identifier of the item to insert.
    /// \param item       The new item to be inserted into the panel.
    /// \param row        The layout row to insert item to.
    /// \param column     The layout column to insert item to.
    /// \param rowSpan    The amount of rows to span across.
    /// \param columnSpan The amount of columns to span across.
    /// \return True if successfully inserted, false otherwise.
    ///
    /// \remarks Yields false if the id already exists.
    ///
    ////////////////////////////////////////////////////////////////////////////
    bool insertItem(
        int id, OfficeMenuItem* item,
        int row, int column,
        int rowSpan, int columnSpan
        );

    ////////////////////////////////////////////////////////////////////////////
    /// Removes a menu item from the panel.
    ///
    /// \param id The unique identifier of the item to remove.
    /// \return True if successfully removed, false otherwise.
    ///
    /// \remarks Yields false if the id is invalid.
    ///
    ////////////////////////////////////////////////////////////////////////////
    bool removeItem(int id);

protected:

    virtual void paintEvent(QPaintEvent*) override;

private:

    ////////////////////////////////////////////////////////////////////////////
    // Members
    //
    ////////////////////////////////////////////////////////////////////////////
    QGridLayout*           m_layout; ///< Defines the grid layout of the panel.
    OfficeMenuHeader*      m_parent; ///< Defines the parent menu header.
    QList<OfficeMenuItem*> m_items;  ///< Holds all menu items in the panel.
    QString                m_text;   ///< Defines the text at the panel bottom.
    int                    m_id;     ///< Defines the unique ID.

    ////////////////////////////////////////////////////////////////////////////
    // Metadata
    //
    ////////////////////////////////////////////////////////////////////////////
    Q_OBJECT

    friend class OfficeMenuHeader;
};

#endif

////////////////////////////////////////////////////////////////////////////////
/// \class OfficeMenuPanel
/// \ingroup Widget
///
/// An ::OfficeMenuPanel can hold multiple items of various types, even items
/// designed by the library user. All that needs to be done is to sublass
/// ::OfficeMenuItem and QWidget, override OfficeMenuItem::widget to return
/// the "this" pointer and to add it through the OfficeMenuPanel::insertItem
/// overloads. The insertItem overloads are capable of specifying the positions
/// of the items within the panel, they can even span across multiple cells.
///
/// \code
/// m_buttonItem = new OfficeMenuButtonItem("Button");
/// m_dropdnItem = new OfficeMenuDropdownItem("Dropdown", { "Item1", "Item2" });
///
/// m_firstPanel->insertItem(id1, m_buttonItem, 0, 0);
/// m_firstPanel->insertItem(id2, m_dropdnItem, 0, 1);
/// \endcode
///
/// Using the code above yields a panel that looks like this:<br><br>
///
/// |      0            1       |<br>
/// |---------------------------|<br>
/// |               Dropdown    |<br>
/// |    Button        v        |  0<br>
/// |                           |<br>
/// |---------------------------|<br>
///
////////////////////////////////////////////////////////////////////////////////
