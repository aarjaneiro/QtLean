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

#ifndef QTLEAN_MAINWINDOW_H
#define QTLEAN_MAINWINDOW_H

#include "QJsonModel.h"
#include <QMainWindow>
#include <QtWidgets>
#include <QSessionManager>
#include "TreeEditor.h"


QT_BEGIN_NAMESPACE
class QDialogButtonBox;

class QPushButton;

QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT


public:
    MainWindow();

private slots:

    void runAlgorithm();

    void configure();

    void lean_dir();


private:
    QLabel *logo;
    TreeEditor *editor;
    QWidget *mainWidget;
    QPushButton *runButton;
    QPushButton *confButton;
    QPushButton *quitButton;
    QDialogButtonBox *dialog;
    QPushButton *leanButton;
    std::basic_string<char> c_dir; // for lean/directory changes
    std::basic_string<char> m_dir; // for main (install) directory
};


#endif //QTLEAN_MAINWINDOW_H