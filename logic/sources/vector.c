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
    short symbol = slope > 180 ? -1 : 1;

    if (slope == 0 || slope == 180) {
        delta_x = magnitude;
        delta_y = 0;
    } else if (slope == G_PI / 2 || slope == -G_PI / 2) {
        delta_x = 0;
        delta_y = magnitude;
    } else {
        delta_x = magnitude * cos(slope) * symbol;
        delta_y = magnitude * sin(slope) * symbol;
    }
    printf("angle next: %f\n", slope * 180 / G_PI);
    return vector_create(s, coordinate_create(s->x + delta_x, s->y + delta_y));
}

double calculate_slope(coordinate* a, coordinate* b) {
    double result = (a->y - b->y) / (a->x - b->x);
    printf("angle prev: %f\n", atan(result) * 180 / G_PI);
    return isfinite(result) ? atan(result) : G_PI / 2;
}
