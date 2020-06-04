#ifndef COORDINATE
#define COORDINATE

typedef struct coordinate_ coordinate;

struct coordinate_ {
    double x;
    double y;
};

/**
 * coordinate constructor.
 *
 * @param x
 * @param y
 * 
 * @return a new coordinate instance
 */
coordinate* coordinate_create(double x, double y);

/**
 * calculate the distance between two points.
 *
 * @param a a charge
 * @param a a charge
 */
double two_points_distance(coordinate* a, coordinate* b);

#endif
