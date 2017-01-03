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


#ifndef QOFFICE_OFFICEMENU_HPP
#define QOFFICE_OFFICEMENU_HPP


// QOffice headers
#include <QOffice/Interfaces/IOfficeWidget.hpp>
#include <QOffice/Widgets/OfficeMenuTopItem.hpp>

// Qt headers
#include <QWidget>


QOFFICE_BEGIN_NAMESPACE


/**
 * This is the description of the class.
 *
 * @class OfficeMenu
 * @author Nicolas Kogler
 * @date January 1st, 2016
 *
 */
class QOFFICE_EXPORT OfficeMenu : public QWidget, public IOfficeWidget
{
public:

    /**
     * Initializes a new instance of OfficeMenu.
     *
     * @param parent The parent widget.
     *
     */
    explicit OfficeMenu(QWidget* parent = nullptr);

    /**
     * Frees all resources used by OfficeMenu.
     *
     */
    ~OfficeMenu();


    QSize sizeHint() const override;


    /**
     * Expands the menu and increases its height.
     *
     */
    void expand(OfficeMenuTopItem* itemToExpand);

    /**
     * Collapses the menu and decreases its height.
     *
     */
    void collapse();


    /**
     * Reimplemented pure virtual function from IOfficeWidget.
     * Retrieves the accent color for this office widget.
     *
     * @returns the current accent color.
     *
     */
    Accent accent() const override;

    /**
     * Reimplmented pure virtual function from IOfficeWidget.
     * Specifies the new accent color for this office widget.
     * Should never be called manually by the programmer, except
     * within the top-level OfficeWindow instance.
     *
     * @param accent New accent color of the office widget.
     *
     */
    void setAccent(Accent accent) override;


    /**
     * Adds one item to the menu items.
     *
     * @param item Item to append.
     *
     */
    void addItem(OfficeMenuTopItem* item);

    /**
     * Inserts one item at the given position.
     *
     * @param pos Position to insert item to.
     * @param item Item to insert.
     *
     */
    void insertItem(int pos, OfficeMenuTopItem* item);

    /**
     * Removes the item at the given index.
     *
     * @param index Index of the item to remove.
     *
     */
    void removeItem(int index);

    /**
     * Removes the given item.
     *
     * @param item Item to remove.
     *
     */
    void removeItem(OfficeMenuTopItem* item);


protected:

    /**
     * Renders the menu bar background in the accent color.
     *
     * @param event Holds nothing we need.
     *
     */
    void paintEvent(QPaintEvent* event) override;

    void resizeEvent(QResizeEvent* event) override;


private:

    // Members
    QList<OfficeMenuTopItem*> m_Items;
    bool m_IsExpanded;

    // Metadata
    Q_OBJECT
};


QOFFICE_END_NAMESPACE


#endif // QOFFICE_OFFICEMENU_HPP
