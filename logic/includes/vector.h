#ifndef VECTOR
#define VECTOR
#include "coordinate.h"

typedef struct vector_ vector;

struct vector_ {
    coordinate* start;
    coordinate* end;
    double magnitude;
};

/**
 * vector constructor.
 *
 * @param c the coordinates of the starting point
 * @param direction the direction of the vector (an angle)
 * @param magnitude the length of the vector
 * 
 * @return a new vector instance
 */
vector* vector_create(coordinate* s, coordinate* e, double magnitude);

vector* vector_create_from_straight_line(coordinate* s, double magnitude, double slope);

double calculate_slope(coordinate* a, coordinate* b);
#endif
