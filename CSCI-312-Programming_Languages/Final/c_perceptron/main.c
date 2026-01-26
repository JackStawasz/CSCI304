#include <stdio.h>
#include <stdlib.h>
#include "perceptron.h"

int main(int argc, char *argv[]) {
    // Building
    char *fname = argv[1];
    Data data = new_Data(fname);
    Model model = new_Model(data);

    // Training
    fit_model(model, data);

    // Testing
    Data testData = new_Data("./train.dat");
    evaluate_model(model, testData);
    delete_Data(testData);

    // Scoring
    run_scoring_engine(model);

    delete_Data(data);
    delete_Model(model);

    return 0;
}

