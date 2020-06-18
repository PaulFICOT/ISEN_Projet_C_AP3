#ifndef VECTOR
#define VECTOR
#include "coordinate.h"

typedef struct vector_ vector;

struct vector_ {
    coordinate* start;
    coordinate* end;
};

/**
 * Vector constructor.
 *
 * @param s the coordinates of the starting point
 * @param e the coordinates of the ending point
 *
 * @return a new vector instance
 */
vector* vector_create(coordinate* s, coordinate* e);

/**
 * Calculates the end point from the slope and the magnitude of the vector
 *
 * @param s the coordinates of the starting point
 * @param e the coordinates of the ending point
 *
 * @return a new vector instance
 */
vector* vector_create_from_straight_line(coordinate* s, double magnitude, double slope);

/**
 * Calculate the slope of a straight line equation carrying two points
 *
 * @param a a point on the straight line
 * @param b an other point on the straight line
 *
 * @return the slope of the line
 */
double calculate_slope(coordinate* a, coordinate* b);
#endif
