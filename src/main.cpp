#include <QApplication>
#include <unistd.h>
#include <iostream>
#include "TreeEditor.h"


int main(int argc, char *argv[]) {
    size_t size = 0;
    char *path=nullptr;
    QApplication app(argc, argv);
    QWidget ui;
    QString cwd = getcwd(path, size);
    cwd.append("Config/config.json");
    std::cout << cwd.toStdString();
    TreeEditor editor(cwd);
    editor.show();
    return QApplication::exec();
}

