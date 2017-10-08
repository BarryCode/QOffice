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
#ifndef QOFFICE_WIDGET_OFFICEMENU_HPP
#define QOFFICE_WIDGET_OFFICEMENU_HPP

#include <QOffice/Widgets/OfficeWidget.hpp>
#include <QWidget>

class OfficeMenuEvent;
class OfficeMenuTextChangedEvent;
class OfficeMenuButtonClickedEvent;
class OfficeMenuItemChangedEvent;
class OfficeMenuHeader;
class OfficeMenuItem;
class QHBoxLayout;
namespace priv { class PinButton; }

////////////////////////////////////////////////////////////////////////////////
/// \class OfficeMenu
/// \brief Defines a ribbon-like menu with panes and items.
/// \author Nicolas Kogler (nicolas.kogler@hotmail.com)
/// \date September 30, 2017
///
////////////////////////////////////////////////////////////////////////////////
class QOFFICE_WIDGET_API OfficeMenu : public QWidget, public OfficeWidget
{
public:

    OffDefaultDtor(OfficeMenu)
    OffDisableCopy(OfficeMenu)
    OffDisableMove(OfficeMenu)

    ////////////////////////////////////////////////////////////////////////////
    /// Initializes a new instance of OfficeMenu and specifies the given \p
    /// parent as owner of this menu.
    ///
    /// \param[in] parent The parent of this menu.
    ///
    ////////////////////////////////////////////////////////////////////////////
    OfficeMenu(QWidget* parent);

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves a pointer to the header item with the given \p id.
    ///
    /// \param[in] id The unique identifier of the item to fetch.
    /// \return The pointer to the header corresponding to \p id.
    ///
    /// \remarks Returns a nullptr if the \p id is invalid.
    ///
    ////////////////////////////////////////////////////////////////////////////
    OfficeMenuHeader* headerById(int id) const;

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves a pointer to the item with the given \p itemId. If one of
    /// \p headerId or \p panelId is -1, the item with the given ID will be
    /// searched dynamically. Note that this can add a significant overhead and
    /// might not even be accurate, since item IDs can theoretically be
    /// identical across different panels and headers.
    ///
    /// \remarks This is equivalent to calling
    ///          menu->headerById(hid)->panelById(pid)->itemById(iid);
    ///
    /// \param[in] headerId The header id that contains the panel for the item.
    /// \param[in] panelId The panel id that contains the item.
    /// \param[in] itemId The unique item id within the panel.
    /// \return The pointer to the item or nullptr otherwise.
    ///
    ////////////////////////////////////////////////////////////////////////////
    OfficeMenuItem* itemById(int headerId, int panelId, int itemId) const;

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves a pointer to the header item with the given \p id. A call to
    /// this is equivalent to OfficeMenu::headerById(id).
    ///
    /// \param[in] id The unique identifier of the item to fetch.
    /// \return The pointer to the header corresponding to \p id.
    ///
    /// \remarks Returns a nullptr if the \p id is invalid.
    ///
    ////////////////////////////////////////////////////////////////////////////
    OfficeMenuHeader* operator [](int id) const;

    ////////////////////////////////////////////////////////////////////////////
    /// Determines whether the ribbon is pinned.
    ///
    /// \return True if pinned, false if collapsed.
    ///
    ////////////////////////////////////////////////////////////////////////////
    bool isPinned() const;

    ////////////////////////////////////////////////////////////////////////////
    /// Specifies whether this menu should be pinned.
    ///
    /// \param[in] pinned True to pin, false otherwise.
    /// \param[in] collapse True to collapse the menu, if \p pinned is false.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void setPinned(bool pinned, bool collapse = true);

    ////////////////////////////////////////////////////////////////////////////
    /// Appends a header item to the menu.
    ///
    /// \param[in] id The unique identifier of the item.
    /// \param[in] text The displayed text of the item.
    /// \return The pointer to the newly created ::OfficeMenuHeader item.
    ///
    /// \remarks Returns a nullptr if the \p id already exists.
    ///
    ////////////////////////////////////////////////////////////////////////////
    OfficeMenuHeader* appendHeader(int id, const QString& text);

    ////////////////////////////////////////////////////////////////////////////
    /// Inserts a header item into the menu. If the \p pos is invalid, this call
    /// equals to OfficeMenu::appendItem(id,text).
    ///
    /// \param[in] pos The position to insert item to.
    /// \param[in] id The unique identifier of the item.
    /// \param[in] text The displayed text of the item.
    /// \return The pointer to the newly created ::OfficeMenuHeader item.
    ///
    /// \remarks Returns a nullptr if the \p id already exists.
    ///
    ////////////////////////////////////////////////////////////////////////////
    OfficeMenuHeader* insertHeader(int pos, int id, const QString& text);

    ////////////////////////////////////////////////////////////////////////////
    /// Removes the item with the given \p id.
    ///
    /// \param[in] id The unique identifier of the item to remove.
    /// \return True if successfully removed, false otherwise.
    ///
    /// \remarks Returns false if the \p id is invalid.
    ///
    ////////////////////////////////////////////////////////////////////////////
    bool removeHeader(int id);

    ////////////////////////////////////////////////////////////////////////////
    /// Expands the menu with the given header and increases its height.
    ///
    /// \param[in] toExpand The header to expand.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void expand(OfficeMenuHeader* toExpand);

    ////////////////////////////////////////////////////////////////////////////
    /// Collapses the menu and decreases its height.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void collapse();

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the desired size for this widget.
    ///
    /// \return The desired width and height, in pixels.
    ///
    ////////////////////////////////////////////////////////////////////////////
    QSize sizeHint() const;

signals:

    ////////////////////////////////////////////////////////////////////////////
    /// This signal is emitted if the user interacted with a menu item inside a
    /// ::OfficeMenuPanel. That can be entering text in a textbox, clicking a
    /// button or choosing a drop-down menu item. It is recommended to read the
    /// documentation on ::OfficeMenuEvent carefully. This is the generic signal
    /// for all event types. Custom events must be handled here.
    ///
    /// \param[in] event Contains useful information about the action.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void itemEvent(OfficeMenuEvent* event);

    ////////////////////////////////////////////////////////////////////////////
    /// This signal is emitted if the user changes text in an e.g. textbox.
    ///
    /// \param[in] event Contains information about the text event.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void textChangedEvent(OfficeMenuTextChangedEvent* event);

    ////////////////////////////////////////////////////////////////////////////
    /// This signal is emitted if the user clicks an e.g. button.
    ///
    /// \param[in] event Contains information about the button event.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void buttonClickedEvent(OfficeMenuButtonClickedEvent* event);

    ////////////////////////////////////////////////////////////////////////////
    /// This signal is emitted if the user changes an item in an e.g. drop-down.
    ///
    /// \param[in] event Contains information about the item event.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void itemChangedEvent(OfficeMenuItemChangedEvent* event);

protected:

    virtual void accentUpdateEvent() override;
    virtual void paintEvent(QPaintEvent*) override;
    virtual void focusOutEvent(QFocusEvent*) override;
    virtual bool eventFilter(QObject*, QEvent*) override;

private:

    void collapseOnFocusLost();

    ////////////////////////////////////////////////////////////////////////////
    // Members
    //
    ////////////////////////////////////////////////////////////////////////////
    QList<OfficeMenuHeader*> m_headers;
    QHBoxLayout*             m_headerLayout;
    QHBoxLayout*             m_panelLayout;
    bool                     m_isExpanded;
    bool                     m_isPinned;
    bool                     m_isTooltipShown;

    ////////////////////////////////////////////////////////////////////////////
    // Metadata
    //
    ////////////////////////////////////////////////////////////////////////////
    Q_OBJECT

    friend class priv::PinButton;
};

#endif

////////////////////////////////////////////////////////////////////////////////
/// \class OfficeMenu
/// \ingroup Widget
///
/// $Detailedclassdesc
///
/// \code
/// <example_code>
/// \endcode
///
////////////////////////////////////////////////////////////////////////////////
