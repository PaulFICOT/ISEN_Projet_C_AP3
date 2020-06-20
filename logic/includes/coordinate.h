#ifndef COORDINATE
#define COORDINATE

#include <math.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct coordinate_ coordinate;

struct coordinate_ {
    double x;
    double y;
};

/**
 * Coordinate constructor.
 *
 * @param x the abscissa
 * @param y the ordinates
 *
 * @return a new coordinate instance
 */
coordinate* coordinate_create(double x, double y);

/**
 * Calculate the distance between two points.
 *
 * @param a a charge
 * @param a a charge
 */
double two_points_distance(coordinate* a, coordinate* b);

#endif
