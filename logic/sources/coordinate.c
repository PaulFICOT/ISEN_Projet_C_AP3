#include "../includes/coordinate.h"

coordinate* coordinate_create(double x, double y) {
    coordinate* c = malloc(sizeof(coordinate));
    c->x = x;
    c->y = y;
    return c;
}

double two_points_distance(coordinate* a, coordinate* b) {
    double result = sqrt(pow(b->x - a->x, 2) + pow(b->y - a->y, 2));
    return isfinite(result) && !isnan(result) ? result : 0;
}
