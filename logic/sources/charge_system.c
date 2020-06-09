#include "../includes/charge_system.h"
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

void delete_charge(charge_system* c_s, charge* c) {
    backtrack(&c_s->charges);
    while (has_next(c_s->charges) && current_charge(c_s) != c) {
        forward(&c_s->charges);
    }
    if (current_charge(c_s) != c) {
        return;
    }
    delete(&c_s->charges);
}

vector* superposition_law(charge_system* c_s, charge* mobile_charge) {
    vector* v = malloc(sizeof(vector));
    v->start = mobile_charge->position;
    double magnitude = 0.0;
    double sum_directions = 0.0;

    backtrack(&c_s->charges);
    int charges_length = length(c_s->charges);
    while (has_next(c_s->charges)) {
        magnitude += coulomb_law(current_charge(c_s), mobile_charge) * (mobile_charge->symbol == (current_charge(c_s))->symbol ? -1 : 1);
        sum_directions += get_direction(mobile_charge->position, (current_charge(c_s))->position);
        forward(&(c_s->charges), 1);
    }
    v->magnitude = magnitude;
    v->direction = sum_directions / (charges_length - 1);
    return v;
}

void calculate_next_speed(charge_system* c_s, charge* c) {
    vector* v = superposition_law(c_s, c);
    c->speeds[c->speeds_index+1] = (v->magnitude / c->weight) * (c->speeds_index + 1) + c->speeds[c->speeds_index];
    c->speeds_index++;
}

void calculate_next_pose(charge_system* c_s, charge* c) {
    while (c->positions_index != c->speeds_index) {
        calculate_next_speed(c_s, c);
    }
    vector* v = superposition_law(c_s, c);
    c->positions[c->positions_index+1] = coordinate_create(
        0.5 * (v->magnitude / c->weight) * pow(c->positions_index, 2) + c->speeds[c->speeds_index] * c->positions_index + c->positions[c->positions_index]->x,
        0.5 * (v->magnitude / c->weight) * pow(c->positions_index, 2) + c->speeds[c->speeds_index] * c->positions_index + c->positions[c->positions_index]->y
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
