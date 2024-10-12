/* 
 This file is part of mygitprompt.

 mygitprompt is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License, version 3 or later
 as published by the Free Software Foundation;

 mygitprompt is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with mygitprompot; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

 Copyright (C) 2024 Oz N Tiram <oz.tiram@gmail.com>
*/

#ifndef COLORS_H
#define COLORS_H

// bash colors
// see man 4 console_codes
// see man 7 ascii

#define STX "\002"
#define SOH "\001"
#define ESC "\033"

#define BOLD SOH ESC "[1m"STX

#define RESET_COLOR SOH ESC "[0m"STX
#define NORMAL SOH ESC "[0m"STX

#define FG_RED SOH ESC "[31m"STX
#define FG_GREEN SOH ESC "[32m"STX
#define FG_WHITE SOH ESC "[97m"STX

#endif

