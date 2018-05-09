#!/usr/bin/env bash
#   interactive_test_1 - test the new bfi version: run a script and checks it  with expected result
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


# echo some commands into bfi command line
#store output to a file. then checks this file with expected result

echo "+++++ +++++>
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.<.>
cl
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++..
>>>
+++++ +++++.
<<<
>>>
..
" | bfi > tmp.out

# file equality is checked with hash equality
TMP_HASH=$(sha512sum tmp.out | cut -f 1 -d  ' ' )
OK_HASH=$(sha512sum test.out | cut -f 1 -d  ' ')

[[ "$TMP_HASH" == "$OK_HASH" ]]


