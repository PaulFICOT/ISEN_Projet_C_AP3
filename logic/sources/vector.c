#include "../includes/vector.h"
#include <math.h>
vector vector_create(coordinate c, double direction, double magnitude) {
    vector v;
    v.start = c;
    v.direction = direction;
    v.magnitude = magnitude;
}

double get_direction(coordinate a, coordinate b) {
    return atan((b.x - a.x) / (a.y - b.y));
}