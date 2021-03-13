// Copyright (c) 2021 Aaron Janeiro Stone
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, write to the Free Software Foundation,
// Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-convert-member-functions-to-static"

#include "MainWindow.h"
#include "TreeEditor.h"
#include "MonoContainer.h"
#include <QDialogButtonBox>
#include <QSessionManager>
#include <QtWidgets>
#include <fstream>
#include <iostream>

MainWindow::MainWindow() {
    QString cwd = "assets/config/config.json";
    std::cout << "\nConfiguration loaded at: ";
    std::cout << cwd.toStdString();

    // Initialize widgets
    logo = new QLabel;
    editor = new TreeEditor(cwd);
    mainWidget = new QWidget;
    auto *mainLayout = new QVBoxLayout;
    runButton = new QPushButton(tr("&Run Algorithm"));
    confButton = new QPushButton(tr("&Configure"));
    quitButton = new QPushButton(tr("&Quit"));

    dialog = new QDialogButtonBox(Qt::Horizontal);
    dialog->addButton(runButton, QDialogButtonBox::ActionRole);
    dialog->addButton(confButton, QDialogButtonBox::ActionRole);
    dialog->addButton(quitButton, QDialogButtonBox::RejectRole);
    connect(runButton, &QPushButton::clicked, this, &MainWindow::runAlgorithm);
    connect(confButton, &QPushButton::clicked, this, &MainWindow::configure);
    connect(quitButton, &QPushButton::clicked, this, &MainWindow::close);

    QPixmap pix("assets/logo.png");
    logo->setPixmap(pix);

    auto *description = new QLabel(
            "Aaron Janeiro Stone (2021) \n \n "
            "Usage: Configure your settings and click `Run Algorithm` to launch.");
    description->setAlignment(Qt::AlignCenter);

    // Set widgets in main window
    mainLayout->addWidget(logo);
    mainLayout->addWidget(description);
    mainLayout->addWidget(dialog);
    mainLayout->setAlignment(logo, Qt::AlignHCenter);
    mainLayout->setAlignment(description, Qt::AlignTop);
    mainLayout->setAlignment(dialog, Qt::AlignCenter);

    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);
    setWindowTitle(tr("QtLean"));
}




void MainWindow::runAlgorithm() {
    // Move config
    std::ifstream source("assets/config/config.json", std::ios::binary);
    std::ofstream destination("Lean/Launcher/bin/Debug/config.json", std::ios::binary);
    destination << source.rdbuf();
    std::cout << "\nSuccessfully copied config.\n";
    auto mono = MonoContainer("QuantConnect.Lean.Launcher", "Lean/Launcher/bin/Debug/QuantConnect.Lean.Launcher.exe");
    void *ret = mono.Exec();
    printf("%", &ret);
}

void MainWindow::configure() { editor->show(); }

#pragma clang diagnostic pop