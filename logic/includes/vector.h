#ifndef VECTOR
#define VECTOR
#include "coordinate.h"

typedef struct vector_ vector;

struct vector_ {
    coordinate* start;
    coordinate* end;
    double direction;
    double magnitude;
};

/**
 * vector constructor.
 *
 * @param c
 * @param direction
 * @param magnitude
 * 
 * @return a new vector instance
 */
vector* vector_create(coordinate* c, double direction, double magnitude);

/**
 * Calculate the direction of a vector given two points
 * 
 * @param first_point a point
 * @param second_point a point
 * 
 * @return an angle representing the direction
 */
double get_direction(coordinate* first_point, coordinate* second_point);

#endif
