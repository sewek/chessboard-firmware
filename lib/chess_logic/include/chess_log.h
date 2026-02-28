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
#include <zephyr/logging/log.h>

#define CHESS_ZEPHYR_LOG 1
#define print_debug(...) LOG_DBG(__VA_ARGS__)
#define print_info(...) LOG_INF(__VA_ARGS__)
#define print_warning(...) LOG_WRN(__VA_ARGS__)
#define print_error(...) LOG_ERR(__VA_ARGS__)

#else

#include <stdio.h>

#define print_debug(...) printf(__VA_ARGS__)
#define print_info(...) printf(__VA_ARGS__)
#define print_warning(...) printf(__VA_ARGS__)
#define print_error(...) printf(__VA_ARGS__)

#endif

#endif

#endif  // CHESS_LOG_H