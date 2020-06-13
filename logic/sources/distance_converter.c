#include "../includes/distance_converter.h"
#include <math.h>

double nm_to_m(double nm) {
    return pow(nm, -9);
}

double m_to_nm(double m) {
    return pow(m, 9);
}
