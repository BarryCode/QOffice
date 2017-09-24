////////////////////////////////////////////////////////////////////////////////
//
// QOffice - The office framework for Qt
// Copyright (C) 2016-2018 Nicolas Kogler
//
// This file is part of the Design module.
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

#include <QOffice/Design/OfficeAccent.hpp>
#include <QOffice/Exceptions/OfficeAccentException.hpp>

OffAnonymous(QColor g_colors[Office::CustomAccent+1])

const QColor& OfficeAccent::color(Office::Accent accent)
{
    if (!isValid(accent))
    {
        throw OfficeAccentException(OffCurrentFunc, static_cast<int>(accent));
    }

    return g_colors[accent];
}

const QColor OfficeAccent::lightColor(Office::Accent accent)
{
    if (!isValid(accent))
    {
        throw OfficeAccentException(OffCurrentFunc, static_cast<int>(accent));
    }

    return g_colors[accent].lighter(130);
}

const QColor OfficeAccent::veryLightColor(Office::Accent accent)
{
    if (!isValid(accent))
    {
        throw OfficeAccentException(OffCurrentFunc, static_cast<int>(accent));
    }

    return g_colors[accent].lighter(200);
}

const QColor OfficeAccent::darkColor(Office::Accent accent)
{
    if (!isValid(accent))
    {
        throw OfficeAccentException(OffCurrentFunc, static_cast<int>(accent));
    }

    return g_colors[accent].darker(130);
}

const QColor OfficeAccent::veryDarkColor(Office::Accent accent)
{
    if (!isValid(accent))
    {
        throw OfficeAccentException(OffCurrentFunc, static_cast<int>(accent));
    }

    return g_colors[accent].darker(200);
}

bool OfficeAccent::isValid(Office::Accent accent)
{
    auto value = static_cast<int>(accent);

    // The custom accent will _always_ be the last accent, so we can safely
    // determine whether 0 <= value <= CustomAccent.
    return value >= 0 && value <= Office::CustomAccent;
}

void OfficeAccent::setCustomColor(const QColor& color)
{
    g_colors[Office::CustomAccent] = color;
}

QColor g_colors[Office::CustomAccent+1] =
{
    QColor(0x2b579a),
    QColor(0xa4373a),
    QColor(0x217346),
    QColor(0xb83B1d),
    QColor(0x68217a),
    QColor(0xf00bae),
};
