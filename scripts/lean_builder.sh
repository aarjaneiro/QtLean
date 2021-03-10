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

(mkdir lean_bin && mkdir lean_bin/Data) || echo "lean_bin directory exists -- overwriting files..."
cd Lean || eval "git clone http://github.com/QuantConnect/Lean && cd Lean"
nuget restore || dotnet restore || exit 1
msbuild -p:Configuration=Release || dotnet msbuild -p:Configuration=Release|| exit 1
cp -r Launcher/bin/Release/* ../lean_bin
cp -r Data/* ../lean_bin/Data

if [ "$1" != -ne ]; then
  echo "Building with examples"
  mkdir ../Algorithm.CSharp || exit
  mkdir ../Algorithm.Python || exit
  cp -r Algorithm.CSharp/* ../Algorithm.CSharp
  cp -r Algorithm.Python/* ../Algorithm.Python
fi

cd .. && rm -r Lean -f
echo "Successfully created Lean binaries"

# == Testing with examples == (requires user input)
#if [ "$1" != -ne ]; then
#  cd ../lean_bin || exit 1
#  echo "Testing..."
#  echo "----------"
#  mono ./QuantConnect.Lean.Launcher.exe --
#fi
exit 0
