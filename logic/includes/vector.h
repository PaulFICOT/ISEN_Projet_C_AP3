#ifndef VECTOR
#define VECTOR
#include "coordinate.h"

typedef struct vector_ vector;

struct vector_ {
    coordinate start;
    double direction;
    double magnitude;
};

vector vector_create(coordinate c, double direction, double magnitude);

double get_direction(coordinate first_point, coordinate second_point);

#endif