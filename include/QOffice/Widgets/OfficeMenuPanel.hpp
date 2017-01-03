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


#ifndef QOFFICE_OFFICEMENUPANEL_HPP
#define QOFFICE_OFFICEMENUPANEL_HPP


// QOffice headers
#include <QOffice/Widgets/OfficeMenuItem.hpp>
#include <QOffice/Widgets/Enums/OfficeMenuEnums.hpp>

// Qt headers
#include <QWidget>


QOFFICE_BEGIN_NAMESPACE


class OfficeMenuTopItem;


/**
 * Defines a panel that contains multiple items
 * of various kinds, such as a button or textbox.
 *
 * @class OfficeMenuPanel
 * @author Nicolas Kogler
 * @date January 2nd, 2016
 *
 */
class QOFFICE_EXPORT OfficeMenuPanel : public QWidget
{
public:

    /**
     * Initializes a new instance of OfficeMenuPanel.
     *
     * @param parent The parent menu item.
     *
     */
    OfficeMenuPanel(OfficeMenuTopItem* parent = nullptr,
                    PanelLayoutType type = PanelLayoutType::Grid);

    /**
     * Constructs a panel from a name.
     *
     * @param name Name of the panel.
     *
     */
    OfficeMenuPanel(const QString& name);

    /**
     * Disposes of all sub items.
     *
     */
    ~OfficeMenuPanel();


    QSize sizeHint() const;

    /**
     * Retrieves the text of the panel.
     *
     * @returns the displayed text.
     *
     */
    const QString& text() const;

    /**
     * Retrieves the bounding rectangle of the panel,
     * including the separator of the panel.
     *
     * @returns the bounds.
     *
     */
    const QRect& bounds() const;

    /**
     * Retrieves all the sub menu items.
     *
     * @returns all the sub menu items.
     *
     */
    const QList<OfficeMenuItem*>& items() const;


    /**
     * Specifies the displayed text.
     *
     * @param text Text to display underneath all items.
     *
     */
    void setText(const QString& text);

    /**
     * Adds the specified item to the list of items.
     *
     * @param item Item to add to the menu items.
     *
     */
    void addItem(OfficeMenuItem* item);

    /**
     * Inserts a new item at the specified position.
     *
     * @param pos Index to insert item to.
     * @param item The item itself to insert.
     *
     */
    void insertItem(int pos, OfficeMenuItem* item);

    /**
     * Removes and deletes the item at the given index.
     *
     * @param index Index of the item.
     *
     */
    void removeItem(int index);

    /**
     * Removes and deletes the specified item.
     *
     * @param item Item to remove and delete.
     *
     */
    void removeItem(OfficeMenuItem* item);

    /**
     * Removes all the items.
     *
     */
    void removeAll();


protected:

    /**
     * Renders this panel. It only contains a
     * bottom-aligned label and a panel separator.
     *
     * @param event Holds nothing we need.
     *
     */
    virtual void paintEvent(QPaintEvent* event) override;


private:

    // Members
    OfficeMenuTopItem* m_ParentItem;
    QLayout*           m_Layout;
    QString            m_Text;
    QRect              m_Bounds;
    PanelLayoutType    m_Type;

    QList<OfficeMenuItem*> m_Items;

    // Metadata
    Q_OBJECT

    // Friends
    friend class OfficeMenuTopItem;
};


QOFFICE_END_NAMESPACE


#endif // QOFFICE_OFFICEMENUPANEL_HPP
