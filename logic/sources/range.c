#include "../includes/range.h"

range range_create(int min, int max) {
    range r = {min = min, max = max};
    return r;
}