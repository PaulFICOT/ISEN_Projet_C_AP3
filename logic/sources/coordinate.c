#include "../includes/coordinate.h"

coordinate coordinate_create(double x, double y) {
    coordinate c = {x = x, y = y};
    return c;
}