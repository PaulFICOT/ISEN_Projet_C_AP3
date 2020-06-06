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
    roots* roots;
};

/**
 * quadratic_polynomial constructor.
 *
 * @param a the x² factor
 * @param b the x factor
 * @param c the constant
 * 
 * @return a new quadratic_polynomial instance
 */
quadratic_polynomial* quadratic_polynomial_create(double a, double b, double c);

/**
 * calulate the delta of a quadratic polynomial
 * 
 * @param q_p a quadratic polynomial
 */
void calculate_delta(quadratic_polynomial* q_p);

/**
 * calulate the roots of a quadratic polynomial
 * 
 * @param q_p a quadratic polynomial
 */
void calculate_roots(quadratic_polynomial* q_p);

#endif
