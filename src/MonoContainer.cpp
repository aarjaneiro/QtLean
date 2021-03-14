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

#include <QtCore>
#include <iostream>
#include <QThread>
#include <thread>
#include "MonoContainer.h"
#include "QLeanThread.h"

MonoContainer::MonoContainer() = default;

int MonoContainer::Exec() {
    std::cout << "=======================\n Entering Lean process \n=======================\n";
    auto *qthread = new QThread;
    auto *qThreadWorker = new QLeanThread;
    qThreadWorker->moveToThread(qthread);
    QAbstractEventDispatcher::connect(qthread, SIGNAL(started()), qThreadWorker, SLOT(RunLean()));
    QAbstractEventDispatcher::connect(qThreadWorker, SIGNAL(lean_exit()), qthread, SLOT(quit()));
    QAbstractEventDispatcher::connect(qthread, SIGNAL(finished()), qThreadWorker, SLOT(deleteLater()));
    QAbstractEventDispatcher::connect(qthread, SIGNAL(finished()), qthread, SLOT(deleteLater()));
    qthread->start();
    while (!(qthread->isFinished())) {
        sleep(1); // To fix crashing, try waiting for user input (SIGTRAP?)
    }
    qthread->quit();
    std::cout << "=======================\n Exited Lean process \n=======================\n";
    return 0;
}

