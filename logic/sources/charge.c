#include "../includes/charge.h"
#include <stdlib.h>

charge* charge_create(double x, double y, enum symbol symbol, double force, double weight, short is_fixed) {
    charge* ch = malloc(sizeof(charge));
    coordinate* c = coordinate_create(x, y);
    ch->position = c;
    ch->symbol = symbol;
    ch->force = force;
    ch->weight = weight;
    ch->is_fixed = is_fixed;
    ch->positions_index = 0;
    ch->speeds_index = 0;
    return ch;
}

short charge_is_itself(charge* ca, charge* cb) {
    return ca->position->x == cb->position->x && ca->position->y == cb->position->y;
}