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

#pragma once
#ifndef QOFFICE_DESIGN_OFFICEIMAGE_HPP
#define QOFFICE_DESIGN_OFFICEIMAGE_HPP

#include <QOffice/Config.hpp>

////////////////////////////////////////////////////////////////////////////////
/// \class OfficeImage
/// \brief Provides useful pixel manipulation functions for QImage and QPixmap.
/// \author Nicolas Kogler (nicolas.kogler@hotmail.com)
/// \date September 23, 2017
///
////////////////////////////////////////////////////////////////////////////////
class QOFFICE_DESIGN_API OfficeImage
{
public:

    ////////////////////////////////////////////////////////////////////////////
    /// Converts an image to grayscale, while keeping the original image
    /// untouched. Do not call this function in QWidget::paintEvent, since it
    /// is potentially expensive. Rather keep a pre-computed grayscale image
    /// somewhere in your class and use it directly in QWidget::paintEvent.
    ///
    /// \param[in] original The original image to convert to grayscale.
    /// \return A copy of the original image with a grayscale palette.
    ///
    ////////////////////////////////////////////////////////////////////////////
    QImage convertToGrayscale(const QImage& original);

    ////////////////////////////////////////////////////////////////////////////
    /// Converts an pixmap to grayscale, while keeping the original pixmap
    /// untouched. Do not call this function in QWidget::paintEvent, since it
    /// is potentially expensive. Rather keep a pre-computed grayscale pixmap
    /// somewhere in your class and use it directly in QWidget::paintEvent.
    ///
    /// \param[in] original The original pixmap to convert to grayscale.
    /// \return A copy of the original pixmap with a grayscale palette.
    ///
    ////////////////////////////////////////////////////////////////////////////
    QPixmap convertToGrayscale(const QPixmap& original);
};

#endif

////////////////////////////////////////////////////////////////////////////////
/// \class OfficeImage
/// \ingroup Design
///
/// A way to use the OfficeImage::convertToGrayscale function is as follows:
///
/// \code
/// void setIcon(const QImage& icon)
/// {
///     m_iconEnable = icon;
///     m_iconDisable = OfficeImage::convertToGrayscale(icon);
/// }
///
/// void paintEvent(QPaintEvent*)
/// {
///     QPainter painter(this);
///     painter.drawImage(QPoint(), (enabled()) ? m_iconEnable : m_iconDisable;
/// }
/// \endcode
///
////////////////////////////////////////////////////////////////////////////////
