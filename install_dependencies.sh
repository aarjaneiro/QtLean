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
if [ ! -s /usr/lib/libpython3.6m.so ]; then
  echo "Downloading Python3.6"
  cd /tmp || echo "Unable to cd into /tmp!" && exit 1
  wget https://www.python.org/ftp/python/3.6.8/Python-3.6.8.tgz
  tar xvzf Python-3.6.8.tgz
  cd Python-3.6.8 || exit 1
  ./configure
  make
  make DESTDIR=/usr install || sudo make install || echo "Error: Insufficient permissions! Run again as super user (sudo)" && exit 1
fi

if [ ! -s /usr/include/mono ]; then
  (
    echo "Downloading Mono"
    cd /tmp || echo "Unable to cd into /tmp!" && exit 1
    wget https://github.com/mono/mono/archive/refs/tags/mono-6.12.0.137.tar.gz
    tar xvzf mono-6.12.0.137.tar.gz
    cd mono-mono-6.12.0.137 || exit 1
    autoconf
    autoupdate
    ./autogen.sh
    make
    make get-monolite-latest
    make DESTDIR=/usr install || sudo make install
  ) || echo "Mono install failed - try manually installing at https://www.mono-project.com/ and then re-run this script." && exit 1
fi

if [ ! -s /usr/include/qt6 ]; then
  echo "Downloading Qt6"
  cd /tmp || echo "Unable to cd into /tmp!" && exit 1
  wget https://download.qt.io/official_releases/qt/6.0/6.0.3/single/qt-everywhere-src-6.0.3.tar.xz
  tar xf qt-everywhere-src-6.0.3.tar.xz
  cd qt-everywhere-src-6.0.3 || exit 1
  ./configure
  make
  make DESTDIR=/usr install || sudo make install || echo "Error: Insufficient permissions! Run again as super user (sudo)" && exit 1
fi
