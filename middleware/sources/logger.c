#include "../includes/logger.h"
#include "../../enums.h"
#include <stdlib.h>

log* log_create(enum log_level log_level, char* message) {
    log* l = malloc(sizeof(log));
    l->log_level = log_level;
    l->message = message;
    return l;
}

void send(enum log_level l, char* m) {
    /* c'est ici qu'on fait des chocapics */
}

void critical(char* message) {
    send(CRITICAL, message);
}

void error(char* message) {
    send(ERROR, message);
}

void warning(char* message) {
    send(WARNING, message);
}

void debug(char* message) {
    send(DEBUG, message);
}

void notice(char* message) {
    send(NOTICE, message);
}

void info(char* message) {
    send(INFO, message);
}