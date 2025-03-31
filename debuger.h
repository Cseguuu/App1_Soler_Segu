// debug.h
#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <time.h>

// Niveles de debug (0-3)
#define DEBUG_LEVEL 3 

// Colores para terminal
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define RESET   "\x1B[0m"

// Macros de logging
#define LOG_ERROR(fmt, ...) \
    if(DEBUG_LEVEL >= 1) { \
        time_t now = time(NULL); \
        printf(RED "[ERROR][%.19s] %s:%d: " fmt RESET "\n", \
               ctime(&now), __FILE__, __LINE__, ##__VA_ARGS__); \
    }

#define LOG_WARN(fmt, ...) \
    if(DEBUG_LEVEL >= 2) { \
        time_t now = time(NULL); \
        printf(YELLOW "[WARN][%.19s] %s:%d: " fmt RESET "\n", \
               ctime(&now), __FILE__, __LINE__, ##__VA_ARGS__); \
    }

#define LOG_INFO(fmt, ...) \
    if(DEBUG_LEVEL >= 3) { \
        time_t now = time(NULL); \
        printf(GREEN "[INFO][%.19s] " fmt RESET "\n", \
               ctime(&now), ##__VA_ARGS__); \
    }

#define LOG_DEBUG(fmt, ...) \
    if(DEBUG_LEVEL >= 4) { \
        time_t now = time(NULL); \
        printf(BLUE "[DEBUG][%.19s] %s:%d: " fmt RESET "\n", \
               ctime(&now), __FILE__, __LINE__, ##__VA_ARGS__); \
    }

// Macro para verificar condiciones críticas
#define CHECK(expr, msg) \
    if(!(expr)) { \
        LOG_ERROR("Check failed: %s. " msg, #expr); \
        exit(EXIT_FAILURE); \
    }

#endif // DEBUG_H