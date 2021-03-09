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

#ifndef QTLEAN_TREEEDITOR_H
#define QTLEAN_TREEEDITOR_H

#include "QJsonModel.h"

#include <QDialog>

QT_BEGIN_NAMESPACE
class QDialogButtonBox;

class QPushButton;

QT_END_NAMESPACE

class TreeEditor : public QWidget {
Q_OBJECT

public:
    explicit TreeEditor(const QString &jsonName, QWidget *parent = nullptr);

private slots:

    void submit();

    void revert();

    void to_default();


private:
    QPushButton *submitButton;
    QPushButton *revertButton;
    QPushButton *defaultButton;
    QPushButton *quitButton;
    QDialogButtonBox *buttonBox;
    QJsonModel *model;
};


#endif //QTLEAN_TREEEDITOR_H
