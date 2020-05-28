#include "../includes/quadratic_polynomial.h"
#include <math.h>

void calculate_delta(quadratic_polynomial* q_p) {
    q_p->delta = pow(q_p->b, 2) - 4 * q_p->a * q_p->c;
}

void calcuate_roots(quadratic_polynomial* q_p) {
    if (q_p == 0) {
        q_p->roots.x_c = - q_p->b / 2 * q_p->a;
    } else {
        q_p->roots.x_a = (-q_p->b - sqrtf(q_p->delta)) / (2 * q_p->a);
        q_p->roots.x_b = (-q_p->b + sqrtf(q_p->delta)) / (2 * q_p->a);
    }
}
