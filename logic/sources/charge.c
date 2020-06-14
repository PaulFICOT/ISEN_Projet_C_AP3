#include "../includes/charge.h"
#include <stdlib.h>
#include <math.h>
charge* charge_create(double x, double y, enum symbol symbol, double force, double weight, short is_fixed) {
    charge* ch = malloc(sizeof(charge));
    coordinate* c = coordinate_create(x, y);
    ch->position = c;
    ch->last_position = c;
    ch->speed = POSE_INTERVAL;
    ch->last_speed = 0;
    ch->symbol = symbol;
    ch->force = force;
    ch->weight = weight;
    ch->is_fixed = is_fixed;
    ch->time = 0;
    return ch;
}

double coulomb_law(charge* a, charge* b) {
    double result = COULOMB_CONST * (fabs((a->force + b->force) * ELEMENTARY_CHARGE)/pow(two_points_distance(a->position, b->position), 2));
    return isfinite(result) && !isnan(result) ? result : 0;
}

short charge_is_itself(charge* a, charge* b) {
    return two_points_distance(a->position, b->position) != 0;
}

charge* random_charge(short is_fixed) {
    return charge_create(
        rand() % 20 * (rand() % 2 == 1 ? -1 : 1),
        rand() % 12 * (rand() % 2 == 1 ? -1 : 1),
        rand() % 2 == 1 ? POSITIVE : NEGATIVE,
        rand() % 11 * (rand() % 2 == 1 ? -1 : 1),
        ((rand() % 9) + 1) * pow(10,-31),
        is_fixed
    );
}
