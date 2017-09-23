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

#include <QOffice/Design/OfficeImage.hpp>
#include <QImage>
#include <QPixmap>

QImage OfficeImage::convertToGrayscale(const QImage& original)
{
    int imgWidth = original.width();
    int imgHeight = original.height();

    // Copies and converts the image to ARGB32. We need this format since the
    // algorithm remains the same everytime, for the sake of simplicity.
    QImage result = original.copy().convertToFormat(QImage::Format_ARGB32);

    for (int y = 0; y < imgHeight; y++)
    {
        // Modify the image scanline-per-scanline. We prefer this method over
        // QImage::setPixel because it is a lot faster and we require this
        // speed if we need to generate a lot of grayscaled images.
        uchar* scanLine = result.scanLine(y);
        for (int x = 0; x < imgWidth; x++)
        {
            // One color entry takes up 4 bytes (32-bit), hence multiply by 4.
            QRgb& pixel = *reinterpret_cast<QRgb*>(scanLine + x * 4);
            qint32 gray = qGray(pixel);

            pixel = qRgba(gray, gray, gray, qAlpha(pixel));
        }
    }

    return result;
}

QPixmap OfficeImage::convertToGrayscale(const QPixmap& original)
{
    return QPixmap::fromImage(convertToGrayscale(original.toImage()));
}
