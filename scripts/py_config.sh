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

# Help message
if [ "$1" == --help ]; then
  printf "Lean Python Configuration Utility
---------------------------------
Usage: bash py_config.sh [location]
Arguments:
       location --  Path to libpython3.6m.so (Linux) or libpython3.6m.dylib (OSX)
                    Note: if not specified, this script will attempt to find it within your environment.
"
  exit 0
elif [ -n "$1" ]; then
  PY_FLAGS="$1"
  PY_PREF="$PY_FLAGS"
  if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    MAP_CONF="<dllmap os=\"linux\" dll=\"python3.6m\" target=\"$PY_PREF\"/>"
  elif [[ "$OSTYPE" == "darwin"* ]]; then
    MAP_CONF="<dllmap os=\"osx\" dll=\"python3.6m\" target=\"$PY_PREF\"/>"
  fi
else
  # Check for correct python version
  PY_FLAGS=$(python3-config --includes)
  PY_PREF=$(python3-config --prefix)
  if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    MAP_CONF="<dllmap os=\"linux\" dll=\"python3.6m\" target=\"$PY_PREF/lib/libpython3.6m.so\"/>"
  elif [[ "$OSTYPE" == "darwin"* ]]; then
    MAP_CONF="<dllmap os=\"osx\" dll=\"python3.6m\" target=\"$PY_PREF\/lib/libpython3.6m.dylib/>"
  fi
fi

# Check if valid
PY_FLAGS=$(echo "$PY_FLAGS" | awk '{print $1;}')
if [[ "$PY_FLAGS" != *"python3.6m"* ]]; then
  echo "ERROR: Python 3.6 must be configured as the environment interpreter or be specified!"
  exit 1
fi
echo "Valid Python 3.6 environment located: $PY_PREF"

# If no error, write configuration
echo "Writing Python configuration to Python.Runtime.dll.config"

cat <<EOF >>lean_bin/Python.Runtime.dll.config
<?xml version="1.0" encoding="utf-8"?>
<configuration>
    $MAP_CONF
</configuration>
EOF
exit 0
