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
#ifndef LIB_TTY_COLOR_H
#define LIB_TTY_COLOR_H

#include <stdarg.h>


/*
 * ANSI escape code:
 *      https://en.wikipedia.org/wiki/ANSI_escape_code
 */
typedef enum{
    
    BLACK  = 48,
    RED    = 49,
    GREEN  = 50,
    YELLOW = 51,
    BLUE   = 52,
    PURPLE = 53,
    CYAN   = 54,
    WHITE  = 55
    
}COLOR;

/*
 * Set stderr colors
 */

//set Foreground(text) color
void setFGerr(COLOR c);

//set Background color
void setBGerr(COLOR c);


/*
 * set stdout colors
 */

//set Foreground(text) color 
void setFG(COLOR c);

//set Background color
void setBG(COLOR c);



/*
 *Following functions set and reset color automatically
 */

//Colorized version of printf
void cprintf(COLOR c,char* fmt,...);

//Colorized version of fprintf(stderr)
void cprintferr(COLOR c,char* fmt,...);


//va_list is not close inside the functions
//Colorized version of vprintf
void cvprintf(COLOR c,char* fmt,va_list arg);

//Colorized version of vfprintf(stderr)
void cvprintferr(COLOR c,char *fmt,va_list arg);



/*
 * Following functions resets default color scheme
 */

//reset stdout
void reset();

//reset stderr
void resetErr();


#endif
