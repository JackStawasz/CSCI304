#include <stdlib.h>
#include "perceptron.h"

int main(int argc, char *argv[])
{
    char *fname = argv[1];
    int number_of_examples = atoi(argv[2]);

    // Building
    double *xcoords = (double*) malloc(number_of_examples * sizeof(double));
    double *ycoords = (double*) malloc(number_of_examples * sizeof(double));
    double *targets = (double*) malloc(number_of_examples * sizeof(double));
    load_data(fname, xcoords, ycoords, targets);

    double *weights = (double*) malloc(DIMENSIONS * sizeof(double));
    initialize(weights);

    // Training
    fit(weights, xcoords, ycoords, targets, number_of_examples);

    // Testing
    // TODO

    // Scoring
    run_scoring_engine(weights);

    free(xcoords);
    free(ycoords);
    free(targets);
    free(weights);

    return 0;
}
