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

#include "MainWindow.h"
#include "TreeEditor.h"
#include "MonoContainer.h"
#include "PythonConfig.h"
#include <QDialogButtonBox>
#include <QSessionManager>
#include <QtWidgets>
#include <fstream>
#include <iostream>
#include <execution>

MainWindow::MainWindow() {
#ifdef NDEBUG
    chdir("/");
#endif
    m_dir = std::string(get_current_dir_name());
    c_dir = m_dir;
    auto conf = std::string(ASSET_DIR).append("/config/");
    std::cout << "Config directory set to " << conf;

    // Initialize widgets
    logo = new QLabel;
    editor = new TreeEditor(conf);
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

    QPixmap pix(std::string(ASSET_DIR).append("/logo.png").data());
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
    auto icon = QIcon(QPixmap(std::string(ASSET_DIR).append("/icon.png").data()));
    this->setWindowIcon(icon);
//    auto tray = QSystemTrayIcon(icon);
//    tray.show();
}

void MainWindow::runAlgorithm() {
    // Dir variables
    auto des = c_dir;
    auto src = m_dir;
    std::ofstream pydestination(des + "/Common/Python/Python.Runtime.dll.config", std::ios::binary);
    pydestination << PyConfig;
    std::cout << "\nSuccessfully copied Python config to " << des + "/Common/Python/Python.Runtime.dll.config" << "\n";


    // Move Lean config
    des.append("/Launcher/config.json");
    src.append(std::string(ASSET_DIR).append("/config/config.json"));
    std::ifstream source(src, std::ios::binary);
    std::ofstream destination(des, std::ios::binary);
    destination << source.rdbuf();
    std::cout << "\nSuccessfully copied config to " << des << "\n";
    std::cout << "\n============== Building Project ==============\n";
    system("msbuild -p:Configuration=Debug || dotnet msbuild -p:Configuration=Debug || exit 1");
    std::cout << "\n============== Running  Project ==============\n";
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
