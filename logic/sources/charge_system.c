#include "../includes/charge_system.h"
#include <stdio.h>
#include <stdlib.h>

charge_system* charge_system_create() {
    charge_system* s = malloc(sizeof(charge_system));
    s->charges = NULL;
    return s;
}

vector* superposition_law(charge_system* c_s, charge* mobile_charge) {
    vector* v = malloc(sizeof(vector));
    v->start = mobile_charge->position;
    double magnitude = 0.0;
    double sum_directions = 0.0;
    int charges_length = length(c_s->charges);
    printf("%i\n", charges_length);
    while (c_s->charges != NULL) {
        printf("%f\n", coulomb_law((charge*) c_s->charges->value, mobile_charge));
        magnitude += coulomb_law((charge*) c_s->charges->value, mobile_charge) * (mobile_charge->symbol == ((charge*)c_s->charges->value)->symbol ? -1 : 1);
        sum_directions += get_direction(mobile_charge->position, ((charge*)c_s->charges->value)->position);
        c_s->charges = c_s->charges->next;
    }
    v->magnitude = magnitude;
    /* we substract 1 because the mobile charge is in c_s->charges */
    v->direction = sum_directions / (charges_length - 1);
    return v;
}

void add_charge(charge_system* c_s, charge* ch) {
    if (c_s->charges == NULL) {
        c_s->charges = linked_list_create(ch);
        return;
    }
    push(c_s->charges, ch);
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
    while (c_s->charges != NULL) {
        if ((two_points_distance(((charge*) c_s->charges->value)->position, coord) - (CHARGE_RADIUS/8.0) * 2.0) < 0.0) {
            return 0;
        }
        c_s->charges = c_s->charges->next;
    }
    return 1;
}
