/*
 *   bfi - execute brainfuck programs
 *   Copyright (C) 2017 Filippo Ranza
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef HELP_H_
#define HELP_H_

char* help = "Usage : bfi [options] [program file] [program arguments]\n"
"Options:\n"
"\t-i      : run interactive mode\n"
"\t-e code : run code given as argument(omit program file)\n"
"\t-d      : enable debug mode\n"
"\t-D      : enable wait debug mode\n"
"\t-W      : enable warnings\n"
"\t-I      : ignores (discards) program arguments\n"
"\t-r file : reads from file instead of stdin\n"
"\t-w file : writes to file instead of stdout\n"
"\t-h      : show this help and exit\n"
"Read the man page for more information\n";



#endif /* HELP_H_ */
