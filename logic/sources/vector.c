#include "../includes/vector.h"
#include "../includes/coordinate.h"
#include "gtk/gtk.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

vector* vector_create(coordinate* s, coordinate* e) {
    vector* v = malloc(sizeof(vector));
    v->start = s;
    v->end = e;
    return v;
}

vector* vector_create_from_straight_line(coordinate* s, double magnitude, double slope) {
    double delta_x, delta_y;
    if (slope == 0) {
        delta_x = magnitude;
        delta_y = 0;
    } else if (slope == G_PI / 2) {
        delta_x = 0;
        delta_y = magnitude;
    } else {
        delta_x = magnitude *  (slope > 0 ? cos(slope) : sin(slope));
        delta_y = magnitude * (slope > 0 ? sin(slope) : cos(slope));
    }
    return vector_create(s, coordinate_create((fabs(s->x) - delta_x ) * (s->x > 0 ? 1 : -1), (fabs(s->y) - delta_y) * (s->y > 0 ? 1 : -1)));
}

double calculate_slope(coordinate* a, coordinate* b) {
    double result = (a->y - b->y) / (a->x - b->x);
    return isfinite(result) ? atan(result) : G_PI / 2;
}
