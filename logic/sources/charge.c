#include "../includes/charge.h"
#include <stdlib.h>
#include <math.h>
charge* charge_create(double x, double y, enum symbol symbol, double force, double weight, short is_fixed) {
    charge* ch = malloc(sizeof(charge));
    coordinate* c = coordinate_create(x, y);
    ch->position = c;
    ch->last_position = c;
    ch->speed = coordinate_create(0, 0);
    ch->last_speed = coordinate_create(0, 0);
    ch->symbol = symbol;
    ch->force = force;
    ch->weight = weight;
    ch->is_fixed = is_fixed;
    ch->time = POSE_INTERVAL;
    return ch;
}

double coulomb_law(charge* a, charge* b) {
    double result = COULOMB_CONST * (fabs((a->force + b->force) * ELEMENTARY_CHARGE)/pow(two_points_distance(a->position, b->position), 2));
    return isfinite(result) && !isnan(result) ? result : 0;
}

charge* random_charge(double x, double y, double is_fixed) {
    return charge_create(
        !isfinite(x) ? rand() % 2000 * pow(10, -2) * (rand() % 2 == 1 ? -1 : 1) : x,
        !isfinite(y) ? rand() % 1200 * pow(10, -2) * (rand() % 2 == 1 ? -1 : 1) : y,
        rand() % 2 == 1 ? POSITIVE : NEGATIVE,
        rand() % 10 * pow(10,-12) * (rand() % 2 == 1 ? -1 : 1),
        ((rand() % 900) + 1) * pow(10,-12),
        !isfinite(is_fixed) ? rand() % 2 : is_fixed
    );
}
