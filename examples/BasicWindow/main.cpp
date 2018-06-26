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

#include <QOffice/Widgets/Dialogs/OfficeWindow.hpp>
#include <QOffice/Design/OfficeAccent.hpp>

#include <QApplication>
#include <QMessageBox>
#include <QRandomGenerator>

Office::Accent generateAccent()
{
    return static_cast<Office::Accent>(
        QRandomGenerator::global()->bounded(0, Office::CustomAccent + 1)
    );
}

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    OfficeWindow window;
    OfficeAccent::setCustomColor(Qt::darkGray);

    window.resize(600, 400);
    window.setMinimumSize(600, 400);
    window.setAccent(Office::BlueAccent);
    window.setWindowTitle("BasicWindow");
    window.labelMenu()->addLabelItem(0, "Switch accent", "Changes the accent color randomly.");

    QObject::connect(
        window.labelMenu(),
        &OfficeWindowMenu::itemClicked,
        [&]() {
            window.setAccent(generateAccent());
        }
    );

    QObject::connect(
        window.labelMenu(),
        &OfficeWindowMenu::helpRequested,
        []() {
            QMessageBox msg;
            msg.setText("You requested help.");
            msg.exec();
        }
    );

    window.show();

    return app.exec();
}
