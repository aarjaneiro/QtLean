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

    submitButton = new QPushButton(tr("Submit"));
    submitButton->setDefault(true);
    revertButton = new QPushButton(tr("&Revert"));
    quitButton = new QPushButton(tr("Quit"));

    buttonBox = new QDialogButtonBox(Qt::Vertical);
    buttonBox->addButton(submitButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(revertButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

    connect(submitButton, &QPushButton::clicked, this, &TreeEditor::submit);
    connect(revertButton, &QPushButton::clicked, this, &TreeEditor::revert);
    connect(quitButton, &QPushButton::clicked, this, &TreeEditor::close);

    auto *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(view);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("Cached Table"));
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