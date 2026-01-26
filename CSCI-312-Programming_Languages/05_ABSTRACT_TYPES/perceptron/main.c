#include <stdio.h>
#include <stdlib.h>
#include "perceptron.h"

int main(int argc, char *argv[])
{
    char *fname = argv[1];
    int number_of_examples = atoi(argv[2]);

    // Building
    Data xcoords = new_Data(number_of_examples);
    Data ycoords = new_Data(number_of_examples);
    Data targets = new_Data(number_of_examples);
    load_data(fname, xcoords, ycoords, targets);

    Model model = new_Model();
    initialize_model(model);

    // Training
    fit_model(model, xcoords, ycoords, targets, number_of_examples);

    // Testing
    // TODO

    // Scoring
    run_scoring_engine(model);

    free(xcoords);
    free(ycoords);
    free(targets);
    free(model);

    return 0;
}
