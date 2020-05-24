#include <stdio.h>

typedef struct coordinate_ coordinate;

struct coordinate_ {
    double x;
    double y;
};

coordinate coordinate_create(double x, double y);

double two_points_distance(coordinate a, coordinate b);