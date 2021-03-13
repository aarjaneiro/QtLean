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
echo "Configuring Python"
echo "=================="
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
  MAP_CONF="<dllmap os=\"linux\" dll=\"python3.6m\" target=\"$1\"/>"
elif [[ "$OSTYPE" == "darwin"* ]]; then
  MAP_CONF="<dllmap os=\"osx\" dll=\"python3.6m\" target=\"$1\"/>"
else
  exit 0
fi
echo "Writing Python configuration to Python.Runtime.dll.config"
rm Lean/Common/Python/Python.Runtime.dll.config
cat <<EOF >>Lean/Common/Python/Python.Runtime.dll.config
<?xml version="1.0" encoding="utf-8"?>
<configuration>
    $MAP_CONF
</configuration>
EOF

echo "Building Lean.Launcher"
echo "======================"

cd Lean || exit 1
nuget restore || dotnet restore || exit 1
msbuild -p:Configuration=Debug || dotnet msbuild -p:Configuration=Debug || exit 1
echo "Successfully configured Lean and Python."
echo "========================================"
exit 0
