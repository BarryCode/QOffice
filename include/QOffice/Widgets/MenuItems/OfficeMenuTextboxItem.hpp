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
#ifndef QOFFICE_WIDGETS_MENUITEMS_OFFICEMENUTEXTBOXITEM_HPP
#define QOFFICE_WIDGETS_MENUITEMS_OFFICEMENUTEXTBOXITEM_HPP

#include <QOffice/Widgets/OfficeMenuEvent.hpp>
#include <QOffice/Widgets/OfficeMenuItem.hpp>
#include <QOffice/Widgets/OfficeLineEdit.hpp>

////////////////////////////////////////////////////////////////////////////////
/// \class OfficeMenuTextboxItem
/// \ingroup Widget
///
/// \brief Defines a single-line textbox on the menu.
/// \author Nicolas Kogler
/// \date October 8, 2017
///
/// This menu item will emit a OfficeMenuEvent::TextChanged event when it's
/// contents were altered. For example, use as follows:
///
/// \code
/// QObject::connect(officeMenu, &OfficeMenu::textChangedEvent,
///     [] (OfficeMenuTextChangedEvent* event)
///         {
///             qDebug() << event->currentText();
///         }
///     );
/// \endcode
///
////////////////////////////////////////////////////////////////////////////////
class QOFFICE_WIDGET_API OfficeMenuTextboxItem
    : public OfficeLineEdit
    , public OfficeMenuItem
{
public:

    OffDefaultDtor(OfficeMenuTextboxItem)
    OffDisableCopy(OfficeMenuTextboxItem)
    OffDisableMove(OfficeMenuTextboxItem)

    ////////////////////////////////////////////////////////////////////////////
    /// Initializes a new instance of OfficeMenuTextboxItem and specifies
    /// the given \p initialText as initial text.
    ///
    /// \param[in] initialText The inital text in the textbox.
    ///
    ////////////////////////////////////////////////////////////////////////////
    OfficeMenuTextboxItem(const QString& initialText = QString());

    QWidget* widget() override;

private slots:

    void onTextChanged(QString, QString);
};

#endif
