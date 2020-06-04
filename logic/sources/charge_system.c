#include "../includes/charge_system.h"
#include <stdio.h>
#include <stdlib.h>

charge_system* charge_system_create() {
    charge_system* s = malloc(sizeof(charge_system));
    s->charges_index = 0;
    return s;
}

double coulomb_law(charge* a, charge* b) {
    return COULOMB_CONST * (fabs(a->force * b->force)/pow(two_points_distance(a->position, b->position), 2));
}

vector* superposition_law(charge* charges[], int charges_index, charge* mobile_charge) {
    vector* v = malloc(sizeof(vector));
    v->start = mobile_charge->position;
    double magnitude = 0.0;
    double sum_directions = 0;
    for (int index = 0; index < charges_index; index++) {
        magnitude += coulomb_law(charges[index], mobile_charge) * mobile_charge->symbol == charges[index]->symbol ? -1 : 1;
        sum_directions += get_direction(mobile_charge->position, charges[index]->position);
    }
    v->magnitude = magnitude;
    v->direction = sum_directions / charges_index;
    return v;
}

void add_charge(charge_system* c_s, charge* ch) {
    printf("Coucou\n");
    printf("%f\n", c_s->charges_index);
    printf("Plus maintenant\n");
    // c_s->charges[c_s->charges_index++] = ch;
}

void calculate_next_speed(charge* c, vector* s_l) {
    c->speeds[c->speeds_index+1] = (s_l->magnitude / c->weight) * (c->speeds_index + 1) + c->speeds[c->speeds_index];
    c->speeds_index++;
}

void calculate_next_pose(charge* c, vector* s_l) {
    c->positions[c->positions_index+1]->x = 0.5 * (s_l->magnitude / c->weight) * pow(c->positions_index, 2) + c->speeds[c->speeds_index] * c->positions_index + c->positions[c->positions_index]->x;
    c->positions[c->positions_index+1]->y = 0.5 * (s_l->magnitude / c->weight) * pow(c->positions_index, 2) + c->speeds[c->speeds_index] * c->positions_index + c->positions[c->positions_index]->y;
    c->positions_index++;
}
