#include "../includes/vector.h"
#include "../includes/coordinate.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

vector* vector_create(coordinate* s, coordinate* e, double magnitude) {
    vector* v = malloc(sizeof(vector));
    v->start = s;
    v->end = e;
    v->magnitude = magnitude;
    return v;
}

vector* vector_create_from_straight_line(coordinate* s, double magnitude, double slope) {
    double slope_angle = atan(slope);
    int symbol = magnitude < 0 ? 1 : -1;
    printf("slope: %f - magnitude: %f\n", slope, magnitude * pow(10, 9));

    double delta_x = magnitude * (slope < 0 ? cos(slope_angle) : sin(slope_angle)) * symbol;
    double delta_y = magnitude * (slope < 0 ? sin(slope_angle) : cos(slope_angle)) * symbol;
    return vector_create(s, coordinate_create(s->x - delta_x, s->y - delta_y), magnitude);
}

double calculate_slope(coordinate* a, coordinate* b) {
    double result = (a->y - b->y) / (a->x - b->x);
    return isfinite(result) && !isnan(result) ? result : 0;
}
