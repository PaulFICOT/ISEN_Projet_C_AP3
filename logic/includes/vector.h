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
 * @param c the coordinates of the starting point
 * @param direction the direction of the vector (an angle)
 * @param magnitude the length of the vector
 * 
 * @return a new vector instance
 */
vector* vector_create(coordinate* s, coordinate* e, double direction, double magnitude);

/**
 * Calculate the direction of a vector given two points
 * 
 * @param first_point a point
 * @param second_point a point
 * 
 * @return an angle representing the direction
 */
double get_direction(coordinate* first_point, coordinate* second_point);

coordinate* calculate_end_point(coordinate* a, double slope, double magnitude);

double calculate_slope(coordinate* a, coordinate* b);
#endif
