/*
 *  QOffice: Office UI framework for Qt
 *  Copyright (C) 2016-2017 Nicolas Kogler
 *
 *  This file is part of QOffice.
 *
 *  QOffice is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  QOffice is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with QOffice. If not, see <http://www.gnu.org/licenses/>.
 *
 */


// QOffice headers
#include <QOffice/Design/OfficeImaging.hpp>


QOFFICE_USING_NAMESPACE


QImage
OfficeImaging::toGrayscale(QImage& img)
{
    // Copies the given image and converts it to 32 bpp.
    QImage grayImg = img.copy().convertToFormat(QImage::Format_ARGB32);

    // Iterates through every pixel and grayscales it.
    int w = grayImg.width(), h = grayImg.height();
    for (int i = 0; i < h; i++)
    {
        uchar* scan = grayImg.scanLine(i);
        for (int j = 0; j < w; j++)
        {
            QRgb* pixel = reinterpret_cast<QRgb*>(scan + j*4);
            int gPixel = qGray(*pixel);
            if (gPixel < 195)
                gPixel += 60;

            *pixel = qRgba(gPixel, gPixel, gPixel, qAlpha(*pixel));
        }
    }

    return grayImg;
}


QPixmap
OfficeImaging::toGrayscale(QPixmap& pm)
{
    QImage img = pm.toImage();
    return QPixmap::fromImage(toGrayscale(img));
}
