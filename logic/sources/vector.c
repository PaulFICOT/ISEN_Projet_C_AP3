#include "../includes/vector.h"
#include <math.h>
#include <stdlib.h>

vector* vector_create(coordinate* s, coordinate* e, double direction, double magnitude) {
    vector* v = malloc(sizeof(vector));
    v->start = s;
    v->end = e;
    v->direction = direction;
    v->magnitude = magnitude;
    return v;
}

double get_direction(coordinate* a, coordinate* b) {
    double result = (b->y - a->y) / (b->x - a->x);
    return isfinite(result) && !isnan(result) ? result : 0;
}

coordinate* calculate_end_point(coordinate* a, double slope, double magnitude) {
    coordinate* c = malloc(sizeof(coordinate));
    c->x = magnitude / slope;
    c->y = slope * c->x + (-slope * a->x + a->y);

    return c;
}

double calculate_slope(coordinate* a, coordinate* b) {
    double result = (a->y - b->y) / (a->x - b->x);
    return isfinite(result) && !isnan(result) ? result : 0;
}