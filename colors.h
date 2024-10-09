#ifndef COLORS_H
#define COLORS_H

// bash colors
// see man 4 console_codes
// see man 7 ascii

#define STX "\002"
#define SOH "\001"

#define BOLD SOH"\033[1m"STX

#define RESET_ALL "\033[0m"
#define NORMAL SOH"\033[0m"STX

#define FG_RED SOH"\033[31m"STX
#define FG_GREEN SOH"\033[32m"STX
#define FG_WHITE SOH"\033[97m"STX


#define GREEN_COLOR SOH"\033[32m"STX
#define RESET_COLOR SOH"\033[0m"STX
#endif

