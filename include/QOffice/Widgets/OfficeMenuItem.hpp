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
#ifndef QOFFICE_WIDGET_OFFICEMENUITEM_HPP
#define QOFFICE_WIDGET_OFFICEMENUITEM_HPP

#include <QOffice/Config.hpp>

class OfficeMenuEvent;
class OfficeMenuPanel;
class QWidget;

////////////////////////////////////////////////////////////////////////////////
/// \class OfficeMenuItem
/// \brief OfficeMenuItemdesc
/// \author Nicolas Kogler (nicolas.kogler@hotmail.com)
/// \date September 30, 2017
///
////////////////////////////////////////////////////////////////////////////////
class QOFFICE_WIDGET_API OfficeMenuItem
{
public:

    OffDefaultDtor(OfficeMenuItem)

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the unique identifier of this object.
    ///
    /// \return The unique identifier.
    ///
    ////////////////////////////////////////////////////////////////////////////
    int id() const;

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the parent panel of this item.
    ///
    /// \return The parent panel.
    ///
    ////////////////////////////////////////////////////////////////////////////
    OfficeMenuPanel* panel() const;

    ////////////////////////////////////////////////////////////////////////////
    /// Specifies the unique identifier of this object.
    ///
    /// \param[in] id The new unique identifier.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void setId(int id);

    ////////////////////////////////////////////////////////////////////////////
    /// Specifies the parent panel of this item.
    ///
    /// \param[in] panel The new parent panel.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void setPanel(OfficeMenuPanel* panel);

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the underlying widget of this menu item.
    ///
    /// \return The underlying widget that is rendered.
    ///
    ////////////////////////////////////////////////////////////////////////////
    virtual QWidget* widget() = 0;

protected:

    ////////////////////////////////////////////////////////////////////////////
    /// Emits an item event and forwards it to the corresponding signal within
    /// the topmost OfficeMenu instance.
    ///
    /// \param event The event to emit.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void emitItemEvent(OfficeMenuEvent* event);

private:

    ////////////////////////////////////////////////////////////////////////////
    // Members
    //
    ////////////////////////////////////////////////////////////////////////////
    OfficeMenuPanel* m_parent; ///< Defines the parent panel.
    int              m_id;     ///< Defines the unique ID.
};

#endif

////////////////////////////////////////////////////////////////////////////////
/// \class OfficeMenuItem
/// \ingroup Widget
///
/// The problem we face once again with menu items is that of multiple
/// inheritance. To have the biggest possible reusability, we need to inherit
/// from any QWidget-type and an interface to emit item events simutaneously.
/// The solution is to declare a must-inherit function that returns a pointer
/// to the widget that is to be drawn. The following example is a full-fledged
/// example on how to use OfficeMenuItem:
///
/// \code
/// class OfficeMenuCustomItem : public QPushButton, public OfficeMenuItem
/// {
/// public:
///
///     OfficeMenuCustomItem(const QString& text) : QPushButton(text)
///     {
///         // Translates QPushButton clicks into item events.
///         connect(this, &QPushButton::clicked, [&]()
///             {
///                 emitItemEvent(new OfficeMenuEvent(
///                     this, OfficeMenuItem::ButtonClick
///                     );
///             });
///     }
///
///     QWidget* widget() const override { return this; }
/// };
///
/// This simple example displays a QPushButton in the panel and forwards the
/// click event on it to the OfficeMenu::itemEvent signal through emitItemEvent.
///
/// Most of the items also directly allow you to connect slots to signals. Take
/// a look at the documentation of the item in question.
/// \endcode
///
////////////////////////////////////////////////////////////////////////////////
