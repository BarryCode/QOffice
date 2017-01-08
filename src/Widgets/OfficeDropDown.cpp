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
#include <QOffice/Widgets/OfficeDropDown.hpp>


QOFFICE_USING_NAMESPACE


OfficeDropDown::OfficeDropDown()
    : QCompleter()
    , m_View(new QListView)
    , m_Model(new QStringListModel)
{
    setPopup(m_View);
    setModel(m_Model);
}


void
OfficeDropDown::addItem(const QString& str)
{
    if (!str.isEmpty())
    {
        m_Items.append(str);
        m_Model->setStringList(m_Items);
    }
}


void
OfficeDropDown::removeItem(const QString& str)
{
    if (!str.isEmpty())
        m_Items.removeOne(str);
}


void
OfficeDropDown::removeAll()
{
    m_Items.clear();
}
