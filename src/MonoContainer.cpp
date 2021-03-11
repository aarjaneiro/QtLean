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

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/mono-config.h>
#include "MonoContainer.h"

MonoContainer::MonoContainer(char *domain, char *assembly) {
    mono_config_parse(NULL);
    monoDomain = mono_jit_init(domain);
    monoAssembly = mono_domain_assembly_open(monoDomain, assembly);
}

void *MonoContainer::Exec() {
    char **argv = reinterpret_cast<char **>(mono_assembly_get_name(monoAssembly));
    mono_jit_exec(monoDomain, monoAssembly, 1, argv);
}

MonoContainer::~MonoContainer() {
    mono_jit_cleanup(monoDomain);
    mono_assembly_close(monoAssembly);
}

