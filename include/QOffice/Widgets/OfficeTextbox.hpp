////////////////////////////////////////////////////////////////////////////////
//
// QOffice - The office framework for Qt
// Copyright (C) 2016-2018 Nicolas Kogler
//
// This file is part of the WIDGET module.
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
#ifndef QOFFICE_WIDGETS_OFFICETEXTBOX_HPP
#define QOFFICE_WIDGETS_OFFICETEXTBOX_HPP

#include <QOffice/Config.hpp>
#include <QTextEdit>

////////////////////////////////////////////////////////////////////////////////
/// \class OfficeTextbox
/// \ingroup Widget
///
/// \brief Defines a textbox in the office style.
/// \author Nicolas Kogler
/// \date October 4, 2017
///
/// The OfficeTextbox does, in addition to the redesign, offer you various
/// formats that the input text has to match. Whenever the text is about to
/// change (keyPressEvent), the format is checked against the text. If it does
/// not accept the new text, the event is ignored and nothing happens.
///
/// \code
/// m_officeTextBox->setFormat(OfficeTextbox::HexOnly);
/// \endcode
///
////////////////////////////////////////////////////////////////////////////////
class QOFFICE_WIDGET_API OfficeTextbox : public QTextEdit
{
public:

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Defines various restrictions and formats for the text box.
    /// \enum Format
    ///
    ////////////////////////////////////////////////////////////////////////////
    enum Format
    {
        Default,     ///< Everything is accepted.
        Password,    ///< Everything is displayed as black dots.
        AsciiOnly,   ///< Only ASCII characters are accepted.
        NumberOnly,  ///< Only numbers are accepted (ints and floats).
        IntegerOnly, ///< Only integer numbers are accepted.
        FloatOnly,   ///< Only floating-point numbers are accepted.
        HexOnly,     ///< Only hexadecimal numbers are accepted.
        OctalOnly,   ///< Only octal numbers are accepted.
        BinaryOnly,  ///< Only binary numbers are accepted.
    };

    OffDefaultDtor(OfficeTextbox)
    OffDisableCopy(OfficeTextbox)
    OffDisableMove(OfficeTextbox)

    ////////////////////////////////////////////////////////////////////////////
    /// Creates a new OfficeTextbox with the given \p parent as owner.
    ///
    /// \param[in] parent The owner of this textbox.
    ///
    ////////////////////////////////////////////////////////////////////////////
    OfficeTextbox(QWidget* parent = nullptr);

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the current format of the textbox.
    ///
    /// \return The format of the textbox.
    ///
    ////////////////////////////////////////////////////////////////////////////
    Format format() const;

    ////////////////////////////////////////////////////////////////////////////
    /// Specifies the format of the textbox. This leads to clearing the textbox.
    ///
    /// \param[in] format The new format of the textbox.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void setFormat(Format format);

signals:

    ////////////////////////////////////////////////////////////////////////////
    /// Is emitted once the text inside the box changes.
    ///
    /// \param[in] previous Contains the previous text.
    /// \param[in] current Contains the current text.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void contentChanged(QString previous, QString current);

protected:

    virtual void keyPressEvent(QKeyEvent*) override; // check format rules.

private slots:

     void generateEvent();

private:

    Format m_format;
    QString m_previous;
    bool m_hasTyped;

    Q_OBJECT
};

#endif
