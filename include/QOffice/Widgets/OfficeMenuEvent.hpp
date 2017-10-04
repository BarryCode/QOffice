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
#ifndef QOFFICE_WIDGETS_OFFICEMENUEVENT_HPP
#define QOFFICE_WIDGETS_OFFICEMENUEVENT_HPP

#include <QOffice/Config.hpp>

////////////////////////////////////////////////////////////////////////////////
/// \class OfficeMenuEvent
/// \brief Defines the base class for all menu events.
/// \author Nicolas Kogler (nicolas.kogler@hotmail.com)
/// \date October 4, 2017
///
////////////////////////////////////////////////////////////////////////////////
class QOFFICE_WIDGET_API OfficeMenuEvent
{
public:

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Defines all event types for the OfficeMenu.
    /// \enum Type
    ///
    ////////////////////////////////////////////////////////////////////////////
    enum Type
    {
        Invalid = -1,
        TextChanged,
        ButtonClicked,
        DropdownItemChanged,
        ComboboxItemChanged,
        UserEvent
    };

    OffDefaultDtor(OfficeMenuEvent)
    OffDisableCopy(OfficeMenuEvent)
    OffDisableMove(OfficeMenuEvent)

    ////////////////////////////////////////////////////////////////////////////
    /// Constructs a new OfficeMenuEvent of the given type.
    ///
    /// \param[in] type The type of the event.
    /// \param[in] id The unique identifier of the item.
    ///
    ////////////////////////////////////////////////////////////////////////////
    OfficeMenuEvent(Type type, int id);

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the type of the event.
    ///
    /// \return The type of the event.
    ///
    ////////////////////////////////////////////////////////////////////////////
    Type type() const;

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the unique identifier of the item.
    ///
    /// \return The ID of the item.
    ///
    ////////////////////////////////////////////////////////////////////////////
    int id() const;

    ////////////////////////////////////////////////////////////////////////////
    /// Determines whether this event was accepted.
    ///
    /// \return True if accepted, false otherwise.
    ///
    ////////////////////////////////////////////////////////////////////////////
    bool isAccepted() const;

    ////////////////////////////////////////////////////////////////////////////
    /// Accepts the event.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void accept();

    ////////////////////////////////////////////////////////////////////////////
    /// Ignores the event.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void ignore();

private:

    ////////////////////////////////////////////////////////////////////////////
    // Members
    //
    ////////////////////////////////////////////////////////////////////////////
    Type         m_type;     ///< Defines the type of the event.
    int          m_id;       ///< Defines the ID of the item.
    mutable bool m_accepted; ///< Determines whether this event was accepted.
};

////////////////////////////////////////////////////////////////////////////////
/// \class OfficeMenuTextChangedEvent
/// \brief Defines an event produced by the user changing some text.
/// \author Nicolas Kogler (nicolas.kogler@hotmail.com)
/// \date October 4, 2017
///
////////////////////////////////////////////////////////////////////////////////
class QOFFICE_WIDGET_API OfficeMenuTextChangedEvent : public OfficeMenuEvent
{
public:

    OffDefaultDtor(OfficeMenuTextChangedEvent)
    OffDisableCopy(OfficeMenuTextChangedEvent)
    OffDisableMove(OfficeMenuTextChangedEvent)

    ////////////////////////////////////////////////////////////////////////////
    /// Constructs a new OfficeMenuTextChangedEvent of the given type.
    ///
    /// \param[in] type The type of the event.
    /// \param[in] id The unique identifier of the item.
    /// \param[in] oldT The previous text.
    /// \param[in] newT The current text.
    ///
    ////////////////////////////////////////////////////////////////////////////
    OfficeMenuTextChangedEvent(
        OfficeMenuEvent::Type type, int id,
        const QString& oldT, const QString& newT
        );

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the previous text.
    ///
    /// \return The previous text.
    ///
    ////////////////////////////////////////////////////////////////////////////
    QString previousText() const;

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the current text.
    ///
    /// \return The current text.
    ///
    ////////////////////////////////////////////////////////////////////////////
    QString currentText() const;

private:

    ////////////////////////////////////////////////////////////////////////////
    // Members
    //
    ////////////////////////////////////////////////////////////////////////////
    QString m_oldText;
    QString m_newText;
};

////////////////////////////////////////////////////////////////////////////////
/// \class OfficeMenuButtonClickedEvent
/// \brief Defines an event produced by the user clicking or toggling a button.
/// \author Nicolas Kogler (nicolas.kogler@hotmail.com)
/// \date October 4, 2017
///
////////////////////////////////////////////////////////////////////////////////
class QOFFICE_WIDGET_API OfficeMenuButtonClickedEvent : public OfficeMenuEvent
{
public:

    OffDefaultDtor(OfficeMenuButtonClickedEvent)
    OffDisableCopy(OfficeMenuButtonClickedEvent)
    OffDisableMove(OfficeMenuButtonClickedEvent)

    ////////////////////////////////////////////////////////////////////////////
    /// Constructs a new OfficeMenuButtonClickedEvent of the given type.
    ///
    /// \param[in] type The type of the event.
    /// \param[in] id The unique identifier of the item.
    /// \param[in] toggable Specifies whether the button is toggable.
    /// \param[in] toggled Specifies whether the button is toggled.
    ///
    ////////////////////////////////////////////////////////////////////////////
    OfficeMenuButtonClickedEvent(
        OfficeMenuEvent::Type type, int id,
        bool toggable, bool toggled
        );

    ////////////////////////////////////////////////////////////////////////////
    /// Determines whether the button is toggable.
    ///
    /// \return True if toggable, false otherwise.
    ///
    ////////////////////////////////////////////////////////////////////////////
    bool isToggable() const;

    ////////////////////////////////////////////////////////////////////////////
    /// Determines whether the button is currently toggled. This is always false
    /// if the button was just clicked (in that case isClicked() returns true).
    ///
    /// \return True if toggled, false otherwise.
    ///
    ////////////////////////////////////////////////////////////////////////////
    bool isToggled() const;

private:

    ////////////////////////////////////////////////////////////////////////////
    // Members
    //
    ////////////////////////////////////////////////////////////////////////////
    bool m_isToggable; ///< Determines whether the button is toggable.
    bool m_isToggled;  ///< Determines whether the button is currently toggeled.
};

////////////////////////////////////////////////////////////////////////////////
/// \class OfficeMenuItemChangedEvent
/// \brief Defines an event produced by the user changing an item.
/// \author Nicolas Kogler (nicolas.kogler@hotmail.com)
/// \date October 4, 2017
///
////////////////////////////////////////////////////////////////////////////////
class QOFFICE_WIDGET_API OfficeMenuItemChangedEvent : public OfficeMenuEvent
{
public:

    OffDefaultDtor(OfficeMenuItemChangedEvent)
    OffDisableCopy(OfficeMenuItemChangedEvent)
    OffDisableMove(OfficeMenuItemChangedEvent)

    ////////////////////////////////////////////////////////////////////////////
    /// Constructs a new OfficeMenuItemChangedEvent of the given type.
    ///
    /// \param[in] type The type of the event.
    /// \param[in] id The unique identifier of the item.
    /// \param[in] index The index of the item in the collection.
    /// \param[in] text The displayed text of the item.
    /// \param[in] value The underlying value of the item.
    ///
    ////////////////////////////////////////////////////////////////////////////
    OfficeMenuItemChangedEvent(
        OfficeMenuEvent::Type type, int id, int index,
        const QString& text, const QVariant& value
        );

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the index of the changed item.
    ///
    /// \return The index of the item.
    ///
    ////////////////////////////////////////////////////////////////////////////
    int index() const;

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the displayed text of the changed item.
    ///
    /// \return The text of the item.
    ///
    ////////////////////////////////////////////////////////////////////////////
    QString text() const;

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the underlying value of the changed item. If the item does not
    /// have an underlying value, this equals OfficeMenuEvent::text.
    ///
    /// \return The underlying value.
    ///
    ////////////////////////////////////////////////////////////////////////////
    QVariant value() const;

private:

    ////////////////////////////////////////////////////////////////////////////
    // Members
    //
    ////////////////////////////////////////////////////////////////////////////
    int m_index;      ///< Defines the index of the item within the collection.
    QString m_text;   ///< Defines the displayed text of the item.
    QVariant m_value; ///< Defines the underlying value of the item.
};

#endif

////////////////////////////////////////////////////////////////////////////////
/// \class OfficeMenuEvent
/// \ingroup Widget
///
/// The OfficeMenuEvent is the base class for all events. Even custom events
/// may be defined, though they must be caught using the generic
/// OfficeMenu::itemEvent signal and a static_cast<> must be performed.
///
/// The ID property of the item is always provided in an OfficeMenuEvent.
///
/// \code
/// void onItemEvent(OfficeMenuEvent* event)
/// {
///     // Let FooEvent::Type be an enum value in the FooEvent class.
///     // Always check for types before doing any casts.
///     if (event->type() == FooEvent::Type)
///     {
///         FooEvent* foo = static_cast<FooEvent*>(event);
///         auto prop = foo->someMagicProperty();
///     }
/// }
/// \endcode
///
/// Note: All user-defined events must be greater than or equal to
/// OfficeMenuEvent::UserEvent. Example:
///
/// \code
/// class FooEvent : public OfficeMenuEvent
/// {
/// public:
///
///     enum Foo { Type = OfficeMenuEvent::UserEvent + SomeInternalNumber };
/// }
///
/// // Or if you wish to have them all at one place
///
/// class MyEvents
/// {
///     enum Type
///     {
///         ProgressChanged = OfficeMenuEvent::UserEvent + 0,
///         TextProcessed   = OfficeMenuEvent::UserEvent + 1,
///         ...
///     }
/// }
/// \endcode
///
/// The accept and ignore functionality can be very useful for custom items.
///
/// \code
/// class CustomTextboxItem : public QLineEdit, public OfficeMenuItem
/// {
/// public:
///
///     enum Type { Event = OfficeMenuEvent::UserEvent + arb_num };
///
/// protected:
///
///     void keyPressEvent(QKeyEvent* event) override
///     {
///         MyKeyPressEvent* e = new MyKeyPressEvent(Event, id(), event->key());
///
///         // Send event to topmost OfficeMenu.
///         emitItemEvent(e);
///
///         if (!e.isAccepted())
///         {
///             // Prevent Qt to put the key into the line edit.
///             event->ignore();
///         }
///     }
/// }
/// \endcode
///
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// \class OfficeMenuTextChangedEvent
/// \ingroup Widget
///
/// This event is emitted once the user changes the text in a textbox.
///
/// \code
/// void textChangedEvent(OfficeMenuTextChangedEvent* event)
/// {
///     // Let MyTextBox be an integer defined in class/namespace Identifiers.
///     if (event->id() == Identifiers::MyTextBox)
///     {
///         // Do something with event->previousText() and event->currentText().
///     }
/// }
/// \endcode
///
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// \class OfficeMenuButtonClickedEvent
/// \ingroup Widget
///
/// This event is emitted once the user clicks or toggles a button.
///
/// \code
/// void buttonClickedEvent(OfficeMenuButtonClickedEvent* event)
/// {
///     // Let MyButton be an integer defined in class/namespace Identifiers.
///     if (event->id() == Identifiers::MyButton)
///     {
///         // Do something with event->isToggable() and event->isToggled().
///         // Normally, one knows whether a button is toggable or not. If for
///         // any reason they not, isToggable must be used to determine whether
///         // or not the button is toggable (and toggled).
///     }
/// }
/// \endcode
///
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// \class OfficeMenuItemChangedEvent
/// \ingroup Widget
///
/// This event is emitted once the user changes an item in a drop-down menu or
/// combobox-menu, for example.
///
/// \code
/// void itemChangedEvent(OfficeMenuItemChangedEvent* event)
/// {
///     // Let MyDropdown be an integer defined in class/namespace Identifiers.
///     if (event->id() == Identifiers::MyDropdown)
///     {
///         int index = event->index();      // index within the DD-menu
///         QString text = event->text();    // displayed text in the DD-menu
///         QVariant value = event->value(); // underlying value (text if null)
///
///         // Note: If drop-down items were added through raw C++ code, the
///         // QVariant can contain any supported type by Qt. If items were
///         // added through parsing an XML representing the menu, though, the
///         // QVariant is _always_ of type QMetaType::String.
///     }
/// }
/// \endcode
///
////////////////////////////////////////////////////////////////////////////////
