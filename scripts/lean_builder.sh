#!/bin/bash
#  Copyright (c) 2021 Aaron Janeiro Stone
#
#  Permission is hereby granted, free of charge, to any person obtaining a copy
#  of this software and associated documentation files (the "Software"), to deal
#  in the Software without restriction, including without limitation the rights
#  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#  copies of the Software, and to permit persons to whom the Software is
#  furnished to do so, subject to the following conditions:
#
#  The above copyright notice and this permission notice shall be included in all
#  copies or substantial portions of the Software.
#
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#  SOFTWARE.
(mkdir lean_bin && mkdir lean_bin/Data)|| echo "lean_bin directory exists -- overwriting files..."
cd Lean || eval "git clone http://github.com/QuantConnect/Lean && cd Lean"
nuget restore || dotnet restore || exit 1
msbuild || dotnet msbuild || exit 1
cp -r Launcher/bin/Debug/* ../lean_bin
cp -r Data/* ../lean_bin/Data
if [ "$1" == --e ]; then
  echo "Building with examples"
  mkdir ../Algorithm.CSharp
  mkdir ../Algorithm.Python
  cp -r Algorithm.CSharp/* ../Algorithm.CSharp
  cp -r Algorithm.Python/* ../Algorithm.Python
fi
cp ../config/config.json ../lean_bin
echo "Successfully created Lean binaries"

# == Testing with examples == (requires user input)
#if [ "$1" == --e ]; then
#  cd ../lean_bin || exit 1
#  echo "Testing..."
#  echo "----------"
#  mono ./QuantConnect.Lean.Launcher.exe --
#fi
exit 0