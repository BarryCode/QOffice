////////////////////////////////////////////////////////////////////////////////
//
// QOffice - The office framework for Qt
// Copyright (C) 2016-2018 Nicolas Kogler
//
// This file is part of the $Module module.
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

#include <QOffice/Design/Office.hpp>
#include <QOffice/Design/OfficePalette.hpp>
#include <QOffice/Widgets/OfficeTextbox.hpp>

#include <QKeyEvent>

OfficeTextbox::OfficeTextbox(QWidget* parent)
    : QTextEdit(parent)
    , m_format(Default)
{
    QString css = Office::loadStyleSheet("OfficeTextbox");
    QString co0 = Office::colorToHex(OfficePalette::color(OfficePalette::Background));
    QString co1 = Office::colorToHex(OfficePalette::color(OfficePalette::MenuItemHover));
    QString co2 = Office::colorToHex(OfficePalette::color(OfficePalette::MenuItemFocus));

    setStyleSheet(css.arg(co0, co1, co2));

    // TextChanged <> GenerateEvent
    QObject::connect(
        this,
        &QTextEdit::textChanged,
        this,
        &OfficeTextbox::generateEvent
        );
}

OfficeTextbox::Format OfficeTextbox::format() const
{
    return m_format;
}

void OfficeTextbox::setFormat(OfficeTextbox::Format format)
{
    // The textbox might contain invalid text by now - clear it.
    m_format = format;
    clear();
}

void OfficeTextbox::keyPressEvent(QKeyEvent* event)
{
    auto text = event->text();
    if (!text.isEmpty())
    {
        QString current = m_previous + text;

        if (m_format == AsciiOnly)
        {
            if (!canInputAscii(current))
                return;
        }
        else if (format == NumberOnly)
        {
            if (!canInputInteger(current) && !canInputFloat(current))
                return;
        }
        else if (format == IntegerOnly)
        {
            if (!canInputInteger(current))
                return;
        }
        else if (format == FloatOnly)
        {
            if (!canInputFloat(current))
                return;
        }
        else if (format == HexOnly)
        {
            if (!canInputHex(current))
                return;
        }
        else if (format == OctalOnly)
        {
            if (!canInputOctal(current))
                return;
        }
        else if (format == BinaryOnly)
        {
            if (!canInputBinary(current))
                return;
        }
    }

    QTextEdit::keyPressEvent(event);
}

void OfficeTextbox::generateEvent()
{
    auto current = toPlainText();
    emit contentChanged(m_previous, current);

    m_previous = current;
}

// TODO: canXYZ funcs
