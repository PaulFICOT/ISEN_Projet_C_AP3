#ifndef CHARGE
#define CHARGE

#include "coordinate.h"
#include "enums.h"
#define MAX_ENTRIES 50

typedef struct charge_ charge;

struct charge_ {
    coordinate* position;
    enum symbol symbol;
    double force;
    double weight;
    short is_fixed;
    coordinate* positions[MAX_ENTRIES];
    int positions_index;
    double speeds[MAX_ENTRIES];
    int speeds_index;
};

/**
 * charge constructor.
 * 
 * @param x
 * @param y
 * @param symbol
 * @param force
 * @param weight
 * @param is_fixed
 * 
 * @return a new charge instance
 */
charge* charge_create(double x, double y, enum symbol symbol, double force, double weight, short is_fixed);

/**
 * Check if two charges are the same
 * 
 * @param a a charge
 * @param b a charge
 * 
 * @return true if the two charges are the same, false otherwise
 */
#endif
