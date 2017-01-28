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


#ifndef QOFFICE_OFFICEDROPDOWN_HPP
#define QOFFICE_OFFICEDROPDOWN_HPP


// QOffice headers
#include <QOffice/Config.hpp>

// Qt headers
#include <QCompleter>
#include <QListView>
#include <QStringListModel>


QOFFICE_BEGIN_NAMESPACE


class OfficeListView;


/**
 * Defines a popup menu that holds multiple items.
 *
 * @class OfficeDropDown
 * @author Nicolas Kogler
 * @date January 6th, 2016
 *
 */
class QOFFICE_EXPORT OfficeDropDown : public QCompleter
{
public:

    /**
     * Initializes a new instance of OfficeDropDown.
     *
     */
    OfficeDropDown();


    /**
     * Adds one drop-down menu entry.
     *
     * @param str Text of the entry.
     *
     */
    void addItem(const QString& str);

    /**
     * Removes one drop-down menu entry.
     *
     * @param str Text entry to remove.
     *
     */
    void removeItem(const QString& str);

    /**
     * Removes all drop-down menu entries.
     *
     */
    void removeAll();


signals:

    /**
     * Is emitted when the drop-down is made invisible.
     *
     */
    void closed();


private slots:

    void hid();


private:

    // Members
    OfficeListView*     m_View;
    QStringListModel*   m_Model;
    QStringList         m_Items;

    // Metadata
    Q_OBJECT
};


class OfficeListView : public QListView
{
public:

    OfficeListView();

protected:

    void hideEvent(QHideEvent* event) override;

signals:

    void closed();

private:

    Q_OBJECT
};


QOFFICE_END_NAMESPACE


#endif // QOFFICE_OFFICEDROPDOWN_HPP
