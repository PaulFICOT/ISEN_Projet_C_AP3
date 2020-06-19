#include "../includes/distance_converter.h"

double nm_to_m(double nm) {
    return nm * pow(10, -9);
}

double m_to_nm(double m) {
    return m * pow(10, 9);
}
