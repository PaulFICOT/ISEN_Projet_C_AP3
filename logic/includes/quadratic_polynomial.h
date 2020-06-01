#ifndef QUADRATIC_POLYNOMIAL
#define QUADRATIC_POLYNOMIAL

typedef struct quadratic_polynomial_ quadratic_polynomial;

typedef struct roots_ roots;

struct roots_ {
    double x_a;
    double x_b;
    double x_c;
};

struct quadratic_polynomial_ {
    double a;
    double b;
    double c;
    double delta;
    roots roots;
};

quadratic_polynomial quadratic_polynomial_create(double a, double b, double c);

void calculate_delta(quadratic_polynomial* q_p);

void calculate_roots(quadratic_polynomial* q_p);

#endif
