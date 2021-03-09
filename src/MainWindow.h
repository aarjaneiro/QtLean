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

private:
    QLabel *logo;
    TreeEditor *editor;
    QWidget *mainWidget;
    QPushButton *runButton;
    QPushButton *confButton;
    QPushButton *quitButton;
    QDialogButtonBox *dialog;
};


#endif //QTLEAN_MAINWINDOW_H