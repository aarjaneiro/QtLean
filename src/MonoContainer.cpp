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

#include <iostream>
#include <thread>
#include "MonoContainer.h"
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/mono-config.h>
#include <execution>

bool exitmono;

void *RunLean(void *pVoid) {
    mono_config_parse(NULL);
    chdir("Lean/Launcher/bin/Debug");
    auto monoDomain = mono_jit_init("QuantConnect.Lean.Launcher");
    auto monoAssembly = mono_domain_assembly_open(monoDomain, "QuantConnect.Lean.Launcher.exe");
    char **argv = (char **) mono_assembly_get_name(monoAssembly);
    while (!exitmono) {
        mono_jit_exec(monoDomain, monoAssembly, 1, argv);
    } // should be own process?
    mono_jit_cleanup(monoDomain);
    mono_assembly_close(monoAssembly);
    chdir("../../../..");
}


MonoContainer::MonoContainer() = default;

int MonoContainer::Exec() {
    std::cout << "=======================\n Entering Lean process \n=======================\n";
    pthread_t thread;
    pthread_create(&thread, nullptr, RunLean, nullptr);
    std::cin.get();
    exitmono = true;
    pthread_cancel(thread);
    pthread_detach(thread);
    _pthread_cleanup_buffer();
    std::cout << "=======================\n Exited Lean process \n=======================\n";
    return 0;
}

