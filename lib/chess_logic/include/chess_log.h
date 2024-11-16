/**
 * @file chess_log.h
 * @brief Chess logic library header file.
 */

#ifndef CHESS_LOG_H
#define CHESS_LOG_H

#ifndef CONFIG_CHESS_LIB_DEBUG

#define print_debug(...)
#define print_info(...)
#define print_warning(...)
#define print_error(...)

#else

#ifdef __ZEPHYR__
#include <zephyr/sys/printk.h>
#include <zephyr/zephyr.h>

#define print_debug(...) printk("[ChessLogic] DEBUG: " __VA_ARGS__)
#define print_info(...) printk("[ChessLogic] INFO: " __VA_ARGS__)
#define print_warning(...) printk("[ChessLogic] WARNING: " __VA_ARGS__)
#define print_error(...) printk("[ChessLogic] ERROR: " __VA_ARGS__)

#else

#include <stdio.h>

#define print_debug(...) printf(__VA_ARGS__)
#define print_info(...) printf(__VA_ARGS__)
#define print_warning(...) printf(__VA_ARGS__)
#define print_error(...) printf(__VA_ARGS__)

#endif

#endif

#endif  // CHESS_LOG_H