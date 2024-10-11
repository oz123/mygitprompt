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

