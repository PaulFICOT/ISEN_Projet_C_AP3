#include "../includes/vector.h"

vector* vector_create(coordinate* s, coordinate* e) {
    vector* v = malloc(sizeof(vector));
    v->start = s;
    v->end = e;
    return v;
}

vector* vector_create_from_straight_line(coordinate* s, double magnitude, double angle) {
    double delta_x, delta_y;

    if (angle == 0 || angle == G_PI) {
        delta_x = magnitude;
        delta_y = 0;
    } else if (angle == G_PI / 2 || angle == -G_PI / 2) {
        delta_x = 0;
        delta_y = magnitude;
    } else {
        delta_x = magnitude * cos(angle);
        delta_y = magnitude * sin(angle);
    }
    return vector_create(s, coordinate_create(s->x + delta_x, s->y + delta_y));
}

double calculate_slope_angle(coordinate* a, coordinate* b) {
    double result = (a->y - b->y) / (a->x - b->x);
    return isfinite(result) ? atan(result) : G_PI / 2;
}
