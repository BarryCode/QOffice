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


#ifndef QOFFICE_OFFICEMENUTOPITEM_HPP
#define QOFFICE_OFFICEMENUTOPITEM_HPP


// QOffice headers
#include <QOffice/Widgets/OfficeMenuPanel.hpp>
#include <QOffice/Widgets/Enums/OfficeMenuEnums.hpp>

// Qt headers
#include <QWidget>


QOFFICE_BEGIN_NAMESPACE


class OfficeMenu;


/**
 * Defines one top menu item or "tab menu item".
 *
 * @class OfficeMenuTopItem
 * @author Nicolas Kogler
 * @date January 2nd, 2016
 *
 */
class QOFFICE_EXPORT OfficeMenuTopItem : public QWidget
{
public:

    /**
     * Initializes a new instance of OfficeMenuTopItem.
     *
     * @param parent The parent office menu.
     */
    OfficeMenuTopItem(OfficeMenu* parent);

    /**
     * Disposes of all panels.
     *
     */
    ~OfficeMenuTopItem();


    /**
     * Determines whether this menu item is selected.
     *
     * @returns true if it is selected.
     *
     */
    bool isSelected() const;

    /**
     * Retrieves the text of the top menu item.
     *
     * @returns the displayed text.
     *
     */
    const QString& text() const;

    /**
     * Returns the bounding rectangle of this item.
     * The bounding rectangle is not the entire menu item
     * with menu bar, but rather the little clickable tab.
     *
     * @returns the bounding rectangle.
     *
     */
    const QRect& bounds() const;

    /**
     * Retrieves all the panels of this menu item.
     *
     * @returns all the panels.
     *
     */
    const QList<OfficeMenuPanel*>& panels() const;

    /**
     * Retrieves the panel at the given index.
     * Returns a nullptr if the index is invalid.
     *
     * @returns the specified panel.
     *
     */
    OfficeMenuPanel* panelAt(int index) const;

    /**
     * Retrieves the panel that is visually located
     * at the given position. Returns a nullptr if
     * the given position is not the location of any panel.
     *
     * @returns the specified panel.
     *
     */
    OfficeMenuPanel* panelAt(const QPoint& pos) const;


    /**
     * Selects and expands this top menu item.
     *
     */
    void select();

    /**
     * Collapses this menu item.
     *
     */
    void collapse();

    /**
     * Specifies the displayed text.
     *
     * @param text Text to display on the tab.
     *
     */
    void setText(const QString& text);

    /**
     * Adds the specified panel to the list of panels.
     *
     * @param panel Panel to add to the menu item.
     *
     */
    void addPanel(OfficeMenuPanel* panel);

    /**
     * Adds a new panel with the specified name.
     *
     * @param name Panel with the given name to add.
     *
     */
    void addPanel(const QString& name);

    /**
     * Inserts a new panel at the specified position.
     *
     * @param pos Index to insert panel to.
     * @param panel The panel itself to insert.
     *
     */
    void insertPanel(int pos, OfficeMenuPanel* panel);

    /**
     * Inserts a new panel with the given name at
     * the specified position.
     *
     * @param pos Index to insert panel to.
     * @param name Panel with the given name to insert.
     *
     */
    void insertPanel(int pos, const QString& name);

    /**
     * Removes and deletes the panel at the given index.
     *
     * @param index Index of the panel.
     *
     */
    void removePanel(int index);

    /**
     * Removes and deletes the specified panel.
     *
     * @param panel Panel to remove and delete.
     *
     */
    void removePanel(OfficeMenuPanel* panel);

    /**
     * Removes all the panels.
     *
     */
    void removeAll();


signals:

    void itemExpanded();
    void itemCollapsed();


protected:

    /**
     * Renders this top menu item. It has a translucent
     * background and will overlap with other menu items
     * logically, but not visually.
     *
     * @param event Holds nothing we need.
     *
     */
    virtual void paintEvent(QPaintEvent* event) override;

    /**
     * Puts the item into hovered state if it is hovered.
     *
     * @param event Holds the cursor position.
     *
     */
    virtual void mouseMoveEvent(QMouseEvent* event) override;

    /**
     * Selects this menu item if it is hovered and pressed.
     *
     * @param event Holds the pressed button.
     *
     */
    virtual void mousePressEvent(QMouseEvent* event) override;


private:

    // Members
    OfficeMenu* m_ParentMenu;
    QString     m_Text;
    QRect       m_Bounds;
    bool        m_IsSelected;
    bool        m_IsHovered;

    TI_DirtyRegions m_DirtyRegions;
    QList<OfficeMenuPanel*> m_Panels;

    // Metadata
    Q_OBJECT

    // Friends
    friend class OfficeMenu;
};


QOFFICE_END_NAMESPACE


#endif // QOFFICE_OFFICEMENUTOPITEM_HPP
