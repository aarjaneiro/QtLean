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

#include <QTreeView>
#include <QtWidgets>
#include <QFile>
#include "QJsonModel.h"
#include "TreeEditor.h"

TreeEditor::TreeEditor(const QString &jsonName, QWidget *parent) : QWidget(parent) {
    model = new QJsonModel(this);
    model->load(jsonName);
    model->setHeaderData(0, Qt::Vertical, tr("Key"));
    model->setHeaderData(1, Qt::Vertical, tr("Value"));

    auto *view = new QTreeView;
    view->setModel(model);

    submitButton = new QPushButton(tr("Save"));
    submitButton->setDefault(true);
    revertButton = new QPushButton(tr("&Revert Changes"));
    defaultButton = new QPushButton(tr("Default"));
    quitButton = new QPushButton(tr("Close"));

    buttonBox = new QDialogButtonBox(Qt::Vertical);
    buttonBox->addButton(submitButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(revertButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(defaultButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

    connect(submitButton, &QPushButton::clicked, this, &TreeEditor::submit);
    connect(revertButton, &QPushButton::clicked, this, &TreeEditor::revert);
    connect(defaultButton, &QPushButton::clicked, this, &TreeEditor::to_default);
    connect(quitButton, &QPushButton::clicked, this, &TreeEditor::hide);

    auto *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(view);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("Configuration"));
}

void TreeEditor::submit() {
    auto json_doc = model->json().toJson();
    QFile save("config/config.json");
    save.open(QIODevice::ReadWrite | QIODevice::Text);
    save.write(json_doc);
}

void TreeEditor::revert() {
    model->load("config/config.json");
    model->setHeaderData(0, Qt::Vertical, tr("Key"));
    model->setHeaderData(1, Qt::Vertical, tr("Value"));

    auto *view = new QTreeView;
    view->setModel(model);
}

void TreeEditor::to_default() {
    model->load("config/default_config.json");
    model->setHeaderData(0, Qt::Vertical, tr("Key"));
    model->setHeaderData(1, Qt::Vertical, tr("Value"));

    auto *view = new QTreeView;
    view->setModel(model);
}