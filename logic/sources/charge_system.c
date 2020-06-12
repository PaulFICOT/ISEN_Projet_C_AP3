#include "../includes/charge_system.h"
#include "constants.h"
#include <stdio.h>
#include <stdlib.h>

charge_system* charge_system_create() {
    charge_system* s = malloc(sizeof(charge_system));
    s->charges = NULL;
    return s;
}

void add_charge(charge_system* c_s, charge* ch) {
    if (is_null(c_s->charges)) {
        c_s->charges = linked_list_create(ch);
        return;
    }
    push(c_s->charges, ch);
}

vector* superposition_law(charge_system* c_s, charge* mobile_charge) {
    if (length(c_s->charges) < 2) {
        return NULL;
    }

    double magnitude = 0.0;
    double sum_slopes = 0.0;

    linked_list* iterator = c_s->charges;
    while (!is_null(iterator)) {
        if ((charge*) iterator->value != mobile_charge) {
            double c_l = coulomb_law((charge*) iterator->value, mobile_charge);

            magnitude += c_l;
            sum_slopes += calculate_slope(mobile_charge->position, ((charge*) iterator->value)->position);
        }
        forward(&iterator, 1);
    }
    vector* v = vector_create_from_straight_line(mobile_charge->position, magnitude, sum_slopes / (length(c_s->charges) - 1));
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
    linked_list* iterator = c_s->charges;
    while (!is_null(iterator)) {
        if ((two_points_distance(((charge*) iterator->value)->position, coord) - (CHARGE_RADIUS/8.0) * 2.0) < 0.0) {
            return 0;
        }
        forward(&iterator, 1);
    }
    return 1;
}

charge* get_charge(charge_system* c_s, coordinate* coord) {
    linked_list* iterator = c_s->charges;
    while (!is_null(iterator)) {
        if ((two_points_distance(((charge*) iterator->value)->position, coord) - (CHARGE_RADIUS/8.0)) < 0.0) {
            return (charge*) iterator->value;
        }
        forward(&iterator, 1);
    }
    return NULL;
}

void reset_charge_system(charge_system* c_s) {
    c_s->charges = NULL;
}

void print_charge(charge_system *c_s) {
    linked_list* iterator = c_s->charges;
    while (!is_null(iterator)) {
        printf("(%f, %f)\n", ((charge*) iterator->value)->position->x, ((charge*) iterator->value)->position->y);
        forward(&iterator, 1);
    }
}

float electrostatic_potential(charge* q, coordinate* m) {
    return (q->force*q->symbol)/(4*PI*EPSILON_0*fabs(two_points_distance(q->position, m)));
}

