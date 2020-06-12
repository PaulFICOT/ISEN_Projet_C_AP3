#include "../includes/charge_system.h"
#include "constants.h"
#include <stdio.h>
#include <stdlib.h>

charge_system* charge_system_create() {
    charge_system* s = malloc(sizeof(charge_system));
    s->charges = NULL;
    return s;
}

charge* current_charge(charge_system* c_s) {
    return (charge*) c_s->charges->value;
}

void add_charge(charge_system* c_s, charge* ch) {
    if (is_null(c_s->charges)) {
        c_s->charges = linked_list_create(ch);
        return;
    }
    push(c_s->charges, ch);
}

void delete_charge(charge_system* c_s, charge* ch) {
    backtrack(&c_s->charges);
    while (has_next(c_s->charges) && current_charge(c_s) != ch) {
        forward(&c_s->charges, 1);
    }
    if (current_charge(c_s) != ch) {
        return;
    }
    delete(&c_s->charges);
}

vector* superposition_law(charge_system* c_s, charge* mobile_charge) {
    if (length(c_s->charges) < 2) {
        return NULL;
    }

    double magnitude = 0.0;
    double sum_slopes = 0.0;

    backtrack(&c_s->charges);
    int charges_length = length(c_s->charges);
    while (has_next(c_s->charges)) {
        if (current_charge(c_s) != mobile_charge) {
            double c_l = coulomb_law(current_charge(c_s), mobile_charge);

            magnitude += c_l;
            sum_slopes += calculate_slope(mobile_charge->position, (current_charge(c_s))->position);
        }
        forward(&(c_s->charges), 1);
    }
    vector* v = vector_create_from_straight_line(mobile_charge->position, magnitude, sum_slopes / (charges_length - 1));
    return v;
}

void calculate_next_speed(charge_system* c_s, charge* c) {
    vector* v = superposition_law(c_s, c);
    c->speeds[c->speeds_index+1] = (v->magnitude / c->weight) * (c->speeds_index + 1) * 0.1 + c->speeds[c->speeds_index];
    c->speeds_index++;
}

void calculate_next_pose(charge_system* c_s, charge* c) {
    while (c->positions_index != c->speeds_index) {
        calculate_next_speed(c_s, c);
    }
    vector* v = superposition_law(c_s, c);
    double t = (c->positions_index+1) * 0.1;
    c->positions[c->positions_index+1] = coordinate_create(
        0.5 * (v->magnitude / c->weight) * pow(t, 2) + c->speeds[c->speeds_index] * c->positions_index + c->positions[c->positions_index]->x,
        0.5 * (v->magnitude / c->weight) * pow(t, 2) + c->speeds[c->speeds_index] * c->positions_index + c->positions[c->positions_index]->y
    );
    c->positions_index++;
}

short charge_is_placeable(charge_system* c_s, coordinate* coord) {
    backtrack(&(c_s->charges));
    while (has_next(c_s->charges)) {
        if ((two_points_distance(current_charge(c_s)->position, coord) - (CHARGE_RADIUS/8.0) * 2.0) < 0.0) {
            return 0;
        }
        forward(&(c_s->charges), 1);
    }
    return 1;
}

charge* get_charge(charge_system* c_s, coordinate* coord) {
    backtrack(&(c_s->charges));
    while (has_next(c_s->charges)) {
        if ((two_points_distance(current_charge(c_s)->position, coord) - (CHARGE_RADIUS/8.0)) < 0.0) {
            return current_charge(c_s);
        }
        forward(&(c_s->charges), 1);
    }
    return NULL;
}

void reset_charge_system(charge_system* c_s) {
    c_s->charges = NULL;
}

void print_charge(charge_system *c_s) {
    while (has_next(c_s->charges)) {
        printf("(%f, %f)\n", current_charge(c_s)->position->x, current_charge(c_s)->position->y);
        forward(&c_s->charges, 1);
    }
}

float electrostatic_potential(charge* q, coordinate* m) {
    return (q->force*q->symbol)/(4*PI*EPSILON_0*fabs(two_points_distance(q->position, m)));
}

