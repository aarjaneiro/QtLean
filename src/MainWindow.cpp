/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2021 Aaron Janeiro Stone
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <QtWidgets>
#include "MainWindow.h"
#include <QDialogButtonBox>
#include <QSessionManager>
#include <iostream>
#include "TreeEditor.h"


MainWindow::MainWindow() {
    QString cwd = "config/config.json";
    std::cout << cwd.toStdString();
    logo = new QLabel;
    editor = new TreeEditor(cwd);
    mainWidget = new QWidget;
    auto *mainLayout = new QVBoxLayout;
    runButton = new QPushButton(tr("Run Algorithm"));
    confButton = new QPushButton(tr("Configure"));
    quitButton = new QPushButton(tr("Quit"));

    dialog = new QDialogButtonBox(Qt::Horizontal);
    dialog->addButton(runButton, QDialogButtonBox::ActionRole);
    dialog->addButton(confButton, QDialogButtonBox::ActionRole);
    dialog->addButton(quitButton, QDialogButtonBox::RejectRole);
    connect(runButton, &QPushButton::clicked, this, &MainWindow::runAlgorithm);
    connect(confButton, &QPushButton::clicked, this, &MainWindow::configure);
    connect(quitButton, &QPushButton::clicked, this, &MainWindow::close);

    QPixmap pix("images/logo.png");
    logo->setPixmap(pix);

    auto *description = new QLabel("Aaron Janeiro Stone (2021) \n \n Usage: Configure your settings and click `Run Algorithm` to launch.");
    description->setAlignment(Qt::AlignCenter);

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

}

void MainWindow::configure() {
    editor->show();
}

