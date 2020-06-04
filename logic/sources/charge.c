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
    ch->positions[0] = c;
    ch->positions_index = 0;
    ch->speeds_index = 0;
    return ch;
}

short charge_is_itself(charge* a, charge* b) {
    return two_points_distance(a->position, b->position) != 0;
}
