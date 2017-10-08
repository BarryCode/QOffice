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

QString Office::colorToHex(const QColor& color)
{
    auto a = QString::number(color.alpha(), 16);
    auto r = QString::number(color.red(),   16);
    auto g = QString::number(color.green(), 16);
    auto b = QString::number(color.blue(),  16);

    return '#' + a + r + g + b;
}

QString Office::loadStyleSheet(const QString& name)
{
    static QString basePath = QStringLiteral(":/qoffice/stylesheets/");
    static QString extension = QStringLiteral(".css");

    // Builds the path (basePath + name + .css).
    QFile file(basePath + name + extension);
    if (!file.open(QFile::ReadOnly))
    {
        return QString();
    }

    return QTextStream(&file).readAll();
}

bool Office::isAscii(const QString& str)
{
    foreach (const QChar c, str)
    {
        if (c.unicode() > 127)
            return false;
    }

    return true;
}

bool Office::isInteger(const QString& str)
{
    foreach (const QChar c, str)
    {
        if (!c.isDigit())
            return false;
    }

    return true;
}

bool Office::isDecimal(const QString& str)
{
    bool success;

    // Tries to convert the entire string (since doubles have a complex ruleset
    // of what to appear and when) and sets 'success' to true if successful.
    str.toDouble(&success);

    return success;
}

bool Office::isNumber(const QString& str)
{
    return isInteger(str) || isDecimal(str);
}

bool Office::isHexadecimal(const QString& str)
{
    bool success;

    str.toULongLong(&success, 16);

    return success;
}

bool Office::isOctal(const QString& str)
{
    bool success;

    str.toULongLong(&success, 8);

    return success;
}

bool Office::isBinary(const QString& str)
{
    bool success;

    str.toULongLong(&success, 2);

    return success;
}
