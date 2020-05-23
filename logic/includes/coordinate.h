#include <stdio.h>

typedef struct coordinate_ coordinate;

struct coordinate_ {
    double x;
    double y;
};

coordinate coordinate_create(double x, double y);

char* coordinate_to_string(coordinate c);