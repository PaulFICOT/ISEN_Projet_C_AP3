#include "../includes/quadratic_polynomial.h"
#include <math.h>

quadratic_polynomial quadratic_polynomial_create(double a, double b, double c) {
    quadratic_polynomial q_p;
    q_p.a = a;
    q_p.b = b;
    q_p.c = c;
    calculate_delta(&q_p);
    calculate_roots(&q_p);
    return q_p;
}

void calculate_delta(quadratic_polynomial* q_p) {
    q_p->delta = pow(q_p->b, 2) - 4 * q_p->a * q_p->c;
}

void calculate_roots(quadratic_polynomial* q_p) {
    if (q_p == 0) {
        q_p->roots.x_c = - q_p->b / 2 * q_p->a;
    } else {
        printf("%f, %f, %f\n", -q_p->b, sqrtf(q_p->delta), (2 * q_p->a));
        q_p->roots.x_a = (-q_p->b - sqrtf(q_p->delta)) / (2 * q_p->a);
        q_p->roots.x_b = (-q_p->b + sqrtf(q_p->delta)) / (2 * q_p->a);
    }
}
