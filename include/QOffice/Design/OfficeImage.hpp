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

QOFFICE_CONSTEXPR int c_shadowSize    = 5;
QOFFICE_CONSTEXPR int c_shadowPadding = +c_shadowSize * 2;
QOFFICE_CONSTEXPR int c_shadowBlur    = -c_shadowSize / 4 + 1;

////////////////////////////////////////////////////////////////////////////////
/// \class OfficeImage
/// \ingroup Design
///
/// \brief Provides useful pixel manipulation functions for QImage and QPixmap.
/// \author Nicolas Kogler
/// \date September 23, 2017
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
    static QImage convertToGrayscale(const QImage& original);

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
    static QPixmap convertToGrayscale(const QPixmap& original);

    ////////////////////////////////////////////////////////////////////////////
    /// Generates a drop shadow of the given \p size.
    ///
    /// \param[in] size The size of the drop shadow.
    /// \return The pixmap containing the shadow.
    ///
    ////////////////////////////////////////////////////////////////////////////
    static QPixmap generateDropShadow(const QSize& size);
};

#endif
