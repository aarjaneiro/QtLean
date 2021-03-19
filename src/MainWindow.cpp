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
#include <execution>

MainWindow::MainWindow() {
    m_dir = std::string(get_current_dir_name());
    c_dir = m_dir;
    auto config = m_dir;
    config.append("/lib/QtLean/assets/config/");
    QString cwd = config.data();
    std::cout << "\nConfiguration loaded at: ";
    std::cout << cwd.toStdString() << "config.json";

    // Initialize widgets
    logo = new QLabel;
    editor = new TreeEditor(cwd);
    mainWidget = new QWidget;
    auto *mainLayout = new QVBoxLayout;
    runButton = new QPushButton(tr("&Run Algorithm"));
    confButton = new QPushButton(tr("&Configure"));
    quitButton = new QPushButton(tr("&Quit"));
    leanButton = new QPushButton(tr("&Lean Directory"));

    dialog = new QDialogButtonBox(Qt::Horizontal);
    dialog->addButton(runButton, QDialogButtonBox::ActionRole);
    dialog->addButton(confButton, QDialogButtonBox::ActionRole);
    dialog->addButton(leanButton, QDialogButtonBox::ActionRole);
    dialog->addButton(quitButton, QDialogButtonBox::RejectRole);
    connect(runButton, &QPushButton::clicked, this, &MainWindow::runAlgorithm);
    connect(confButton, &QPushButton::clicked, this, &MainWindow::configure);
    connect(leanButton, &QPushButton::clicked, this, &MainWindow::lean_dir);
    connect(quitButton, &QPushButton::clicked, this, &MainWindow::close);

    QPixmap pix("lib/QtLean/assets/logo.png");
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
    auto icon = QIcon(QPixmap("lib/QtLean/assets/icon.png"));
    this->setWindowIcon(icon);
//    auto tray = QSystemTrayIcon(icon);
//    tray.show();
}

void MainWindow::runAlgorithm() {
    // Move config
    auto des = c_dir;
    auto src = m_dir;
    des.append("/Launcher/bin/Debug/config.json");
    src.append("/lib/QtLean/assets/config/config.json");
    std::ifstream source(src, std::ios::binary);
    std::ofstream destination(des, std::ios::binary);
    destination << source.rdbuf();
    std::cout << "\nSuccessfully copied config to " << des << "\n";
    MonoContainer::Exec();
}

void MainWindow::configure() {
    editor->show();
}

void MainWindow::lean_dir() {
    c_dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                              "/home",
                                              QFileDialog::ShowDirsOnly
                                              | QFileDialog::DontResolveSymlinks).toStdString();
    std::cout << "\nChanging Lean directory to " << std::string(c_dir) << "\n";
    chdir(c_dir.data());
}
