#include "../includes/vector.h"
#include "../includes/coordinate.h"
#include <math.h>
#include <stdlib.h>

vector* vector_create(coordinate* s, coordinate* e) {
    vector* v = malloc(sizeof(vector));
    v->start = s;
    v->end = e;
    return v;
}

vector* vector_create_from_straight_line(coordinate* s, double slope, double magnitude) {
    coordinate* e = malloc(sizeof(coordinate));
    e->x = magnitude / slope;
    e->y = slope * e->x + (-slope * s->x + s->y);

    return vector_create(s, e);
}

double calculate_magnitude(vector* v) {
    return two_points_distance(v->start, v->end);
}

double calculate_slope(coordinate* a, coordinate* b) {
    double result = (a->y - b->y) / (a->x - b->x);
    return isfinite(result) && !isnan(result) ? result : 0;
}
