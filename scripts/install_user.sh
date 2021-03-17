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
echo "Installing library to /usr/lib/qtlean"
mkdir /usr/lib/qtlean || (echo "ERROR: Did you run as root?" && exit 1)
cp -r assets /usr/lib/qtlean
cp qtlean /usr/lib/qtlean
chmod 755 /usr/lib/qtlean/qtlean
echo "Installing executable to /usr/bin/QtLean"
cat <<EOF >>/usr/bin/QtLean
#!/bin/bash
if [[ "$PWD" != *Lean* ]]; then
    echo "WARNING: qtlean should be run from Lean's root directory."
fi
ln -s /usr/lib/qtlean/qtlean . || echo "WARNING: Was not able to make links!"
cp -r /usr/lib/qtlean/assets . || echo "WARNING: Was not able to make config!"
./qtlean
rm qtlean
EOF
chmod 755 /usr/bin/QtLean
