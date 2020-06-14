#include "../includes/charge_system.h"
#include "../../constants.h"
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
            c_l *= ((charge*) iterator->value)->symbol == mobile_charge->symbol ? -1 : 1;
            magnitude += c_l;
            sum_slopes += calculate_slope(mobile_charge->position, ((charge*) iterator->value)->position);
        }
        forward(&iterator, 1);
    }
    vector* v = vector_create_from_straight_line(mobile_charge->position, magnitude, sum_slopes / (length(c_s->charges) - 1));
    return v;
}

void calculate_next_pose(charge_system* c_s, charge* c) {
    vector* v = superposition_law(c_s, c);
    double a = (v->magnitude / c->weight);

    c->speed = a * c->time + c->last_speed;
    c->last_speed = c->speed;

    c->position = coordinate_create(
        0.5 * a * pow(c->time, 2) + c->speed * c->time + c->last_position->x,
        0.5 * a * pow(c->time, 2) + c->speed * c->time + c->last_position->y
    );
    c->last_position = c->position;
    c->time += POSE_INTERVAL;
}

short charge_is_placeable(charge_system* c_s, coordinate* coord) {
    linked_list* iterator = c_s->charges;
    while (!is_null(iterator)) {
        if ((two_points_distance(((charge*) iterator->value)->position, coord) - (CHARGE_RADIUS/20.0) * 2.0) < 0.0) {
            return 0;
        }
        forward(&iterator, 1);
    }
    return 1;
}

charge* get_charge(charge_system* c_s, coordinate* coord) {
    linked_list* iterator = c_s->charges;
    while (!is_null(iterator)) {
        if ((two_points_distance(((charge*) iterator->value)->position, coord) - (CHARGE_RADIUS/20.0)) < 0.0) {
            return (charge*) iterator->value;
        }
        forward(&iterator, 1);
    }
    return NULL;
}

void reset_charge_system(charge_system* c_s) {
    free(c_s->charges);
    c_s->charges = NULL;
}

void print_charge(charge_system *c_s) {
    linked_list* iterator = c_s->charges;
    while (!is_null(iterator)) {
        printf("(%f, %f)\n", ((charge*) iterator->value)->position->x, ((charge*) iterator->value)->position->y);
        forward(&iterator, 1);
    }
}

double electrostatic_potential(charge_system *c_s, coordinate* m) {

    double elec_pot = 0;
    linked_list* iterator = c_s->charges;
    while (!is_null(iterator)) {
        double elec_calc = 1/(4*PI*EPSILON_0);
        elec_calc *= (((charge*) iterator->value)->symbol == NEGATIVE ? -1 : 1)/(fabs(two_points_distance(((charge*) iterator->value)->position, m)));
        elec_pot += elec_calc;
        forward(&iterator, 1);
    }
    return elec_pot;
}
