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
#include <QOffice/Plugins/OfficeMenuPlugin.hpp>
#include <QOffice/Plugins/Extensions/OfficeMenuTaskMenu.hpp>
#include <QOffice/Widgets/OfficeMenu.hpp>

// Qt headers
#include <QtDesigner/QDesignerFormEditorInterface>
#include <QtDesigner/QExtensionManager>
#include <QtPlugin>
#include <QFile>


QOFFICE_USING_NAMESPACE


OfficeMenuPlugin::OfficeMenuPlugin(QObject* parent)
    : QObject(parent)
    , m_IsInitialized(false)
{
}


bool
OfficeMenuPlugin::isInitialized() const
{
    return m_IsInitialized;
}


bool
OfficeMenuPlugin::isContainer() const
{
    return false;
}


QString
OfficeMenuPlugin::name() const
{
    return "off::OfficeMenu";
}


QString
OfficeMenuPlugin::group() const
{
    return "QOffice Base Widgets";
}


QString
OfficeMenuPlugin::includeFile() const
{
    return "QOfficeMenu";
}


QString
OfficeMenuPlugin::domXml() const
{
    QFile xmlFile(":/qoffice/plugins/officemenu.xml");
    if (xmlFile.open(QFile::ReadOnly) != true)
        throw "XML missing for this plugin!";

    return QString(xmlFile.readAll());
}


QString
OfficeMenuPlugin::toolTip() const
{
    return "The main menu of the application.";
}


QString
OfficeMenuPlugin::whatsThis() const
{
    return "The menu that fits best as an extension of the title bar.";
}


QIcon
OfficeMenuPlugin::icon() const
{
    return QIcon(":/qoffice/plugins/officemenu.png");
}


QWidget*
OfficeMenuPlugin::createWidget(QWidget* parent)
{
    return new OfficeMenu(parent);
}


void
OfficeMenuPlugin::initialize(QDesignerFormEditorInterface* form)
{
    if (m_IsInitialized)
        return;

    QExtensionManager* manager = form->extensionManager();
    Q_ASSERT(manager != nullptr);

    manager->registerExtensions(new OfficeMenuTaskMenuFactory(manager),
                                Q_TYPEID(QDesignerTaskMenuExtension));

    m_IsInitialized = true;
}
