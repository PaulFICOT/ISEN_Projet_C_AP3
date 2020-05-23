typedef struct range_ range;

struct range_ {
    int min;
    int max;
};

range range_create(int min, int max);