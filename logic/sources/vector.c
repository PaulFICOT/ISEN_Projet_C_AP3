#include "../includes/vector.h"
#include <math.h>
#include <stdlib.h>

vector* vector_create(coordinate* c, double direction, double magnitude) {
    vector* v = malloc(sizeof(vector));
    v->start = c;
    v->direction = direction;
    v->magnitude = magnitude;
    return v;
}

double get_direction(coordinate* a, coordinate* b) {
    double result = atan((b->x - a->x) / (a->y - b->y));
    return isfinite(result) && !isnan(result) ? result : 0;
}
