#include "../includes/coordinate.h"
#include <math.h>

coordinate coordinate_create(double x, double y) {
    coordinate c = {x = x, y = y};
    return c;
}

double two_points_distance(coordinate a, coordinate b) {
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}
