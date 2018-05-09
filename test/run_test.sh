#!/usr/bin/env bash
#   output_test_1 - test the new bfi version: run test in each subdirectory
#
#   Copyright (c) 2018 Filippo Ranza <filipporanza@gmail.com>
#
#   This program is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation; either version 3 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <http://www.gnu.org/licenses/>.


# search for every available subdirectory
# then search for available .sh files, if so run it.
# in case of error the script immediately exit with error
for i in *; do
    if [[ -d "$i" ]] ; then
        cd "$i"
        SCRIPT=$(echo *sh)
        if [[ "$SCRIPT" != '*sh' ]] ; then
            source "$SCRIPT" || exit 1
        fi
        cd ..
    fi
done
