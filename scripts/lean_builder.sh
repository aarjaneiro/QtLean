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

cd Lean || eval "git clone http://github.com/QuantConnect/Lean && cd Lean"
nuget restore || dotnet restore || exit 1

echo "Successfully restored Lean to $PWD"

# == Testing with examples == (requires user input)
#if [ "$1" != -ne ]; then
#  cd ../lean_bin || exit 1
#  echo "Testing..."
#  echo "----------"
#  mono ./QuantConnect.Lean.Launcher.exe --
#fi
exit 0
