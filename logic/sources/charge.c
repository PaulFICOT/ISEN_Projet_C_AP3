#include "../includes/charge.h"
#include <stdlib.h>
#include <math.h>
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

double coulomb_law(charge* a, charge* b) {
    double result = COULOMB_CONST * (fabs(a->force * b->force)/pow(two_points_distance(a->position, b->position), 2));
    return isfinite(result) && !isnan(result) ? result : 0;
}

short charge_is_itself(charge* a, charge* b) {
    return two_points_distance(a->position, b->position) != 0;
}

charge* random_charge() {
    return charge_create(
        rand() % 50 * (rand() % 2 == 1 ? -1 : 1),
        rand() % 50 * (rand() % 2 == 1 ? -1 : 1),
        rand() % 2 == 1 ? POSITIVE : NEGATIVE,
        rand() % 9 * 10^(-rand()%4),
        rand() % 9 * 10^(-rand()%4),
        rand() % 2
    );
}