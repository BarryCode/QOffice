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


#ifndef QOFFICE_OFFICEIMAGING_HPP
#define QOFFICE_OFFICEIMAGING_HPP


// QOffice headers
#include <QOffice/Config.hpp>

// Qt headers
#include <QImage>
#include <QPixmap>


QOFFICE_BEGIN_NAMESPACE


/**
 * Provides functions for manipulating images.
 *
 * @class OfficeImaging
 * @author Nicolas Kogler
 * @date January 6th, 2016
 *
 */
class QOFFICE_EXPORT OfficeImaging
{
public:

    /**
     * Converts the given image to a grayscale image.
     * Does not change the format of the image, but
     * converts all pixels to gray ones.
     *
     * @param img Image to convert to grayscale.
     *
     */
    static QImage toGrayscale(QImage& img);

    /**
     * Converts the given pixmap to a grayscale pixmap.
     * Uses the OfficeImaging::toGrayscale(QImage&) function.
     *
     * @param pm Pixmap to convert to grayscale.
     *
     */
    static QPixmap toGrayscale(QPixmap& pm);
};


QOFFICE_END_NAMESPACE


#endif // QOFFICE_OFFICEIMAGING_HPP
