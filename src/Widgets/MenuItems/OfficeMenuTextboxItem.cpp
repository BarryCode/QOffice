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

#include <QOffice/Widgets/MenuItems/OfficeMenuTextboxItem.hpp>

OfficeMenuTextboxItem::OfficeMenuTextboxItem(const QString& initialText)
    : OfficeLineEdit()
{
    setText(initialText);
    setTextMargins(1,2,1,2);
    setFocusPolicy(Qt::ClickFocus);

    QObject::connect(
        this,
        &OfficeLineEdit::contentChanged,
        this,
        &OfficeMenuTextboxItem::onTextChanged
        );
}

QWidget* OfficeMenuTextboxItem::widget()
{
    return this;
}

void OfficeMenuTextboxItem::onTextChanged(QString previous, QString current)
{
    OfficeMenuTextChangedEvent event(id(), previous, current);

    emitItemEvent(&event);
}
