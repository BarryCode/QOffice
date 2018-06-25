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

#include <QOffice/Design/OfficeFont.hpp>

#include <QFontDatabase>
#include <QMutex>

static QMutex g_mutex;
static QMap<int, int> g_indices;
static QMap<uint, QFont> g_fonts;

static uint generateKey(int weight, float pointSize)
{
    // Multiplies the size by two in order to avoid half-point sizes.
    uint size = static_cast<uint>(pointSize * 2);

    // With this encoding, theoretically around 256 fonts and more are possible,
    // with all of them having various sizes.
    return (weight << 16) | size;
}

static QString fontPath(int weight)
{
    QString baseString(":/qoffice/fonts/Font-%0.ttf");

    // The fonts are named Font-0, Font-1, and so on in order to dynamically
    // load fonts from resources given a font weight enum value.
    return baseString.arg(QString::number(weight));
}

static bool indexExists(int index)
{
    QMutexLocker locker(&g_mutex);

    return g_indices.contains(index);
}

static bool fontExists(int key)
{
    QMutexLocker locker(&g_mutex);

    return g_fonts.contains(key);
}

const QFont& OfficeFont::font(Weight weight, float pointSize)
{
    auto weightValue = static_cast<int>(weight);
    if (!isValid(weight))
    {
        weight = Regular;
    }

    // Determines whether the combination of weight and pointSize exists.
    auto key = generateKey(weightValue, pointSize);
    if (!fontExists(key))
    {
        int index;

        // Determines whether the font corresponding to the weight itself exists.
        // If it is, we simply construct a new QFont of the given pointSize.
        if (!indexExists(weight))
        {
            // Font itself is not loaded yet. We use the QFontDatabase in order
            // to load a font from the resources.
            index = QFontDatabase::addApplicationFont(fontPath(weightValue));

            g_mutex.lock();
            g_indices.insert(weightValue, index);
            g_mutex.unlock();
        }
        else
        {
            g_mutex.lock();
            index = g_indices.value(weightValue);
            g_mutex.unlock();
        }

        QFont font;

        // Attepts to set the font family. If it does not exist, the family
        // will remain the default one for this operating system.
        if (index != -1)
        {
            auto familyList = QFontDatabase::applicationFontFamilies(index);
            if (!familyList.isEmpty())
            {
                font.setFamily(familyList.at(0));
            }
        }

        font.setPointSizeF(pointSize);

        // Creates a new cache entry for the font and directly returns it.
        QMutexLocker locker(&g_mutex);
        return g_fonts.insert(key, font).value();
    }

    // It is now ensured that there always is a font for the given properties.
    QMutexLocker locker(&g_mutex);
    return g_fonts[key];
}

bool OfficeFont::isValid(int weight)
{
    return weight >= 0 && weight < MaximumWeight;
}
