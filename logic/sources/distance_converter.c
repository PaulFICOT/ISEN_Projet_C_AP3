#include "../includes/distance_converter.h"

/**
 * Converts nanometers to meters
 * 
 * @param nm a distance in nanometers
 **/
double nm_to_m(double nm) {
    return nm * pow(10, -9);
}

/**
 * Converts meters to nanometers
 * 
 * @param m a distance in meters
 **/
double m_to_nm(double m) {
    return m * pow(10, 9);
}
