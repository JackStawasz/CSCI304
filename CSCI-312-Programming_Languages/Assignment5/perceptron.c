#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "perceptron.h"

struct data {
    double **inputs; // 2D matrix of feature inputs
    int *targets; // 1D array of targets
    Shape dimensionality; // Matrix row/col size
};

struct shape {
    int feature_count; // Number of columns
    int example_count; // Number of rows
};

struct model {
    double *weights;
    Shape dimensionality;
};

Data new_Data(const char *fname) {
    Data data = (Data) malloc(sizeof(Data));

    // Open file
    FILE *fp;
    if ((fp = fopen(fname, "r")) == NULL)  {
        fprintf(stderr, "load_data: can't open %s\n", fname);
        exit(1);
    }
    
    // Find dimensions and size of data
    int example_count = 0;
    int feature_count = 0;
    char counting_line[1024]; // Large maximum char length per line
    while(fgets(counting_line, sizeof(counting_line), fp)) {
        if (example_count == 0) { // Find number of columns from 1st line
            char copy_line[1024];
            strcpy(copy_line, counting_line);
            char* token = (char*) strtok(copy_line, " ");
            while (token != NULL) {
                feature_count++;
                token = (char*) strtok(NULL, " ");
            }
        }
        example_count++;
    }
    feature_count -= 1; // remove target from count

    // Re-assign data info to objects
    data->dimensionality = malloc(sizeof(Shape));
    data->dimensionality->example_count = example_count;
    data->dimensionality->feature_count = feature_count;

    // Allocate Memory
    data->inputs = (double**) malloc(example_count * sizeof(double*));
    for (int row=0; row<example_count; row++) {
        data->inputs[row] = (double*) malloc(feature_count * sizeof(double));
    }
    data->targets = (int*) malloc(example_count * sizeof(double));

    // Iterate/Assign elements
    char line[1024];
    rewind(fp); // reset file pointer
    for (int row=0; row<example_count; row++) {
        if (fgets(line, sizeof(line), fp) == NULL) {
            continue; // Bypass incorrect indices
        }
        char* token = (char*) strtok(line, " ");
        for (int col=0; col<feature_count; col++) {
            if (token != NULL) {
                data->inputs[row][col] = strtod(token, NULL);
            }
            token = (char*) strtok(NULL, " ");
        }
        if (token != NULL) {
            data->targets[row] = strtod(token, NULL);
        }
    }

    // Close & Return
    fclose(fp);
    fprintf(stdout, "new_Data: loaded %d examples\n", example_count);
    return data;
}

Model new_Model(const Data data) {
    Model model = malloc(sizeof(struct model));
    model->dimensionality = malloc(sizeof(struct shape));
    model->dimensionality->feature_count = data->dimensionality->feature_count;
    int dimensions = model->dimensionality->feature_count + 1;
    model->weights = (double*) malloc(dimensions * sizeof(double));
    for (int i=0; i<dimensions; i++)
        model->weights[i] = (double) rand() / RAND_MAX;
    return model;
}

static void sgd(Model model, Data data) {
    double *input = data->inputs[0];
    double target = data->targets[0];
    int input_length = model->dimensionality->feature_count + 1;
    for (int i=0; i<input_length; i++) {
        model->weights[i+1] += target * input[i];
    }
    model->weights[0] += target * 1; // Bias term
}

static int predict(Model model, double *feature) {
    double hypothesis = model->weights[0];
    for (int i=0; i < model->dimensionality->feature_count; i++) {
        hypothesis += model->weights[i+1] * feature[i];
    }

    return (hypothesis < 0) ? -1 : 1;
}

void fit_model(Model model, Data data) {
    double hypothesis, target;
    int example_count = data->dimensionality->example_count;
    int feature_count = data->dimensionality->feature_count;

    bool misclassified = true;
    while (misclassified) {
        misclassified = false;
        for (int row=0; row<example_count; row++) {
            hypothesis = predict(model, data->inputs[row]);
            target = data->targets[row];
            if ((hypothesis > 0 && target > 0) || (hypothesis < 0 && target < 0) || target==0) {
                continue; // Skip over correctly classified points
            } else {
                // Save misclassified point to temporary data
                Data misclassified_data = malloc(sizeof(struct data));
                misclassified_data->inputs = malloc(sizeof(double*));
                misclassified_data->inputs[0] = data->inputs[row];
                misclassified_data->targets = malloc(sizeof(int));
                misclassified_data->targets[0] = data->targets[row];

                sgd(model, misclassified_data); // Update weights using misclassified point
                misclassified = true; // Trigger recheck on other points (prevent regression)
            }
        }
    }
}

void run_scoring_engine(const Model model) {
    double x, y;

    printf("Enter x: \n");
    scanf("%lf", &x);

    printf("Enter y: \n");
    scanf("%lf", &y);

    // Save x and y to a feature vector
    double *feature = malloc(2 * sizeof(double));
    feature[0] = x;
    feature[1] = y;

    printf("Prediction = %d\n", predict(model, feature));
}
