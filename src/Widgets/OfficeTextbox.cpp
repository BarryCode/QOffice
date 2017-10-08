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

#include <QOffice/Design/Office.hpp>
#include <QOffice/Design/OfficePalette.hpp>
#include <QOffice/Widgets/OfficeTextbox.hpp>

#include <QKeyEvent>

OfficeTextbox::OfficeTextbox(QWidget* parent)
    : QTextEdit(parent)
    , m_format(Default)
    , m_hasTyped(false)
{
    QString css = Office::loadStyleSheet("OfficeTextbox");
    QString co0 = Office::colorToHex(QColor(Qt::white));
    QString co1 = Office::colorToHex(OfficePalette::color(OfficePalette::MenuItemHover));
    QString co2 = Office::colorToHex(OfficePalette::color(OfficePalette::MenuItemFocus));

    setStyleSheet(css.arg(co0, co1, co2));

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
    // The backspace should always be enabled, regardless of the current
    // format. Any non-printable combinations (like CTRL + A) should always
    // be enabled too in order to ensure useful editing behaviour.
    if (!event->text().isEmpty() && event->key() != Qt::Key_Backspace)
    {
        QString current = m_previous + event->text();

        if (m_format != Default)
        {
            if (m_format == AsciiOnly)
            {
                if (!Office::isAscii(current))
                    return;
            }
            else if (m_format == NumberOnly)
            {
                if (!Office::isNumber(current))
                    return;
            }
            else if (m_format == IntegerOnly)
            {
                if (!Office::isInteger(current))
                    return;
            }
            else if (m_format == FloatOnly)
            {
                if (!Office::isDecimal(current))
                    return;
            }
            else if (m_format == HexOnly)
            {
                if (!Office::isHexadecimal(current))
                    return;
            }
            else if (m_format == OctalOnly)
            {
                if (!Office::isOctal(current))
                    return;
            }
            else if (m_format == BinaryOnly)
            {
                if (!Office::isBinary(current))
                    return;
            }
        }

        m_hasTyped = true;
    }

    if (event->key() == Qt::Key_Backspace)
    {
        // For example, the combination CTRL + A should not count as 'typed'
        // text, whereas the backspace implies a text manipulation.
        m_hasTyped = true;
    }

    QTextEdit::keyPressEvent(event);
}

void OfficeTextbox::generateEvent()
{
    if (!m_hasTyped)
    {
        // Fix: When we use setText() to set the initial text,
        // OfficeMenuTextChangedEvent::previousText would always yield the wrong
        // result for the first time the user types something. Therefore do not
        // emit an event before the user has typed.
        m_previous = toPlainText();
    }
    else
    {
        auto current = toPlainText();
        emit contentChanged(m_previous, current);

        m_previous = current;
    }
}
