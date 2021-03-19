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

#include "MonoContainer.h"
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/mono-config.h>
#include <execution>

void *RunLean() {
    mono_config_parse(NULL);
    chdir("Launcher/bin/Debug");
    auto monoDomain = mono_jit_init("QuantConnect.Lean.Launcher");
    auto monoAssembly = mono_domain_assembly_open(monoDomain, "QuantConnect.Lean.Launcher.exe");
    char **argv = (char **) mono_assembly_get_name(monoAssembly);
    mono_jit_exec(monoDomain, monoAssembly, 1, argv);
    mono_jit_cleanup(monoDomain);
    mono_assembly_close(monoAssembly);
    chdir("../../..");
}


MonoContainer::MonoContainer() = default;

void MonoContainer::Exec() {
    if (fork() == 0) {
        RunLean();
    }
}

