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

#pragma once
#ifndef QOFFICE_WIDGETS_OFFICEMENUPINBUTTON_HPP
#define QOFFICE_WIDGETS_OFFICEMENUPINBUTTON_HPP

#include <QOffice/Config.hpp>
#include <QWidget>

class OfficeMenuHeader;
class OfficeTooltip;

namespace priv
{
class PinButton : public QWidget
{
public:

    OffDefaultDtor(PinButton)
    OffDisableCopy(PinButton)
    OffDisableMove(PinButton)

    PinButton(OfficeMenuHeader* parent);

    QSize sizeHint() const override;

protected:

    virtual void paintEvent(QPaintEvent*) override;
    virtual void enterEvent(QEvent*) override;
    virtual void leaveEvent(QEvent*) override;
    virtual void mousePressEvent(QMouseEvent*) override;
    virtual void mouseReleaseEvent(QMouseEvent*) override;

private slots:

    void onTooltipShown();

private:

    ////////////////////////////////////////////////////////////////////////////
    // Members
    //
    ////////////////////////////////////////////////////////////////////////////
    OfficeMenuHeader* m_parent;
    OfficeTooltip*    m_tooltip;
    QPixmap           m_imgSticky;
    QPixmap           m_imgCollapse;
    bool              m_isHovered;
    bool              m_isPressed;

    Q_OBJECT
};
}

#endif
