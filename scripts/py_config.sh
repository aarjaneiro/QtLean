#!/bin/bash
# Copyright (c) 2021 Aaron Janeiro Stone
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 3 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program; if not, write to the Free Software Foundation,
# Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
  MAP_CONF="<dllmap os=\"linux\" dll=\"python3.6m\" target=\"$1\"/>"
elif [[ "$OSTYPE" == "darwin"* ]]; then
  MAP_CONF="<dllmap os=\"osx\" dll=\"python3.6m\" target=\"$1\"/>"
else
  exit 0
fi
echo "Writing Python configuration to Python.Runtime.dll.config"

rm lean_bin/Python.Runtime.dll.config || echo "Nothing to remove"

cat <<EOF >>lean_bin/Python.Runtime.dll.config
<?xml version="1.0" encoding="utf-8"?>
<configuration>
    $MAP_CONF
</configuration>
EOF
exit 0
