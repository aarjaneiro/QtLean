//
// Created by ajst on 2021-03-07.
//

#include <QTreeView>
#include <QtWidgets>
#include <QFile>
#include "qjsonmodel.h"
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
    connect(revertButton, &QPushButton::clicked, model, &QJsonModel::revert);
    connect(quitButton, &QPushButton::clicked, this, &TreeEditor::close);

    auto *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(view);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("Cached Table"));
}
void TreeEditor::submit() {
        auto json_doc = model->json().toJson();
        QFile save("Config/config.json");
        save.open(QIODevice::ReadWrite | QIODevice::Text);
        save.write(json_doc);
    }

