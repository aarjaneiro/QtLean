//
// Created by ajst on 2021-03-14.
//

#include <mono/metadata/threads.h> // <- use this instead!
#include <mono/jit/jit.h>
#include <QtCore>
#include <mono/metadata/assembly.h>
#include <mono/metadata/mono-config.h>
#include <csignal>
#include <execution>
#include <iostream>
#include <QThread>
#include <thread>
#include "MonoContainer.h"


#ifndef QTLEAN_QTHREADWORKER_H
#define QTLEAN_QTHREADWORKER_H


class QLeanThread : public QObject {
Q_OBJECT
public slots:

    void RunLean() {
        mono_config_parse(NULL);
        chdir("Lean/Launcher/bin/Debug");
        auto monoDomain = mono_jit_init("QuantConnect.Lean.Launcher");
        auto monoAssembly = mono_domain_assembly_open(monoDomain, "QuantConnect.Lean.Launcher.exe");
        char **argv = (char **) mono_assembly_get_name(monoAssembly);
        mono_jit_exec(monoDomain, monoAssembly, 1, argv);
        mono_jit_cleanup(monoDomain);
        mono_assembly_close(monoAssembly);
        chdir("../../../..");
        emit lean_exit();
    }

signals:

    void lean_exit();
};


#endif //QTLEAN_QTHREADWORKER_H
