#ifndef COLORS_H
#define COLORS_H

// bash colors
// see man 4 console_codes
// see man 7 ascii

#define STX "\002"
#define BOLD "\001\033[1m"STX

#define RESET_ALL "\033[0m"
#define NORMAL "\001\033[0m"STX

#define FG_RED "\001\033[31m"STX
#define FG_GREEN "\001\033[32m"STX
#define FG_WHITE "\001\033[97m"STX


#define GREEN_COLOR "\001\033[32m"STX
#define RESET_COLOR "\001\033[0m"STX
#endif

