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

#pragma once
#ifndef QOFFICE_WIDGETS_OFFICEWIDGET_HPP
#define QOFFICE_WIDGETS_OFFICEWIDGET_HPP

#include <QOffice/Config.hpp>

////////////////////////////////////////////////////////////////////////////////
/// \class OfficeWidget
/// \brief The base class for all QOffice widgets.
/// \author Nicolas Kogler (nicolas.kogler@hotmail.com)
/// \date September 22, 2017
///
////////////////////////////////////////////////////////////////////////////////
class QOFFICE_WIDGET_API OfficeWidget
{
public:

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Holds all predefined accents and a custom one.
    /// \enum Accent
    ///
    ////////////////////////////////////////////////////////////////////////////
    enum Accent
    {
        BlueAccent,
        RedAccent,
        GreenAccent,
        OrangeAccent,
        PurpleAccent,
        CustomAccent
    };

    OffDeclareCtor(OfficeWidget)
    OffDefaultDtor(OfficeWidget)
    OffDisableCopy(OfficeWidget)
    OffDisableMove(OfficeWidget)

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the accent of this office widget.
    ///
    /// \return The current accent.
    ///
    ////////////////////////////////////////////////////////////////////////////
    virtual Accent accent() const;

    ////////////////////////////////////////////////////////////////////////////
    /// Specifies the new accent color for this office widget. Does not set the
    /// accent for the child widgets. Consider calling OfficeWindow::setAccent
    /// instead.
    ///
    /// \param accent New accent of the office widget.
    ///
    ////////////////////////////////////////////////////////////////////////////
    virtual void setAccent(Accent accent);

protected:

    ////////////////////////////////////////////////////////////////////////////
    /// This event is triggered whenever the accent was updated. It should
    /// update the surface of the underlying Qt widget.
    ///
    ////////////////////////////////////////////////////////////////////////////
    virtual void accentUpdateEvent();

private:

    ////////////////////////////////////////////////////////////////////////////
    // Members
    //
    ////////////////////////////////////////////////////////////////////////////
    Accent m_accent; ///< Holds the current accent of the office widget.
};

#endif

////////////////////////////////////////////////////////////////////////////////
/// \class OfficeWidget
/// \ingroup Widget
///
/// Why does OfficeWidget not subclass QWidget? The reason is pretty obvious
/// once one decides to write more advanced widgets. If OfficeWidget devires
/// from QWidget, one would not be able to inherit the functionality of e.g.
/// QTreeView, meaning they need to reimplement everything from scratch. The
/// correct way to use OfficeWidget is as follows:
///
/// \code
/// class OfficeListView : public QListView, public OfficeWidget
/// {
/// protected:
///
///     void paintEvent(QPaintEvent*) override
///     {
///         const QColor& accentColor = OfficeAccent::get(m_accent);
///
///         // draw something using the accent color.
///     }
/// };
/// \endcode
///
////////////////////////////////////////////////////////////////////////////////
