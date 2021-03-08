//
// Created by ajst on 2021-03-07.
//

#ifndef QTLEAN_TREEEDITOR_H
#define QTLEAN_TREEEDITOR_H

#include "qjsonmodel.h"

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

private:
    QPushButton *submitButton;
    QPushButton *revertButton;
    QPushButton *quitButton;
    QDialogButtonBox *buttonBox;
    QJsonModel *model;
};


#endif //QTLEAN_TREEEDITOR_H
