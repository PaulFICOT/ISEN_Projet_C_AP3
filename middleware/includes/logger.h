#ifndef LOGGER
#define LOGGER

#include "../../enums.h"

typedef struct log_ log;
struct log_ {
    enum log_level log_level;
    char* message;
};

log* log_create(enum log_level l, char* m);

void send(enum log_level l, char* m);

void critical(char* message);
void error(char* message);
void warning(char* message);
void debug(char* message);
void notice(char* message);
void info(char* message);

#endif