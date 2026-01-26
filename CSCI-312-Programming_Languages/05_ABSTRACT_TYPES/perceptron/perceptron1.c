#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "perceptron.h"
#include <string.h>

struct data {
    double *elements;
};

struct model {
    double *weights;
};

Data new_Data(int number_of_examples)
{
    Data data = (Data) malloc(sizeof(Data));
    data->elements = (double*) malloc(number_of_examples * sizeof(double));
    return data;
}

void load_data(char *fname, Data x, Data y, Data targets)
{
    FILE *fp;

    if ((fp = fopen(fname, "r")) == NULL)  {
        fprintf(stderr, "load_data: can't open %s\n", fname);
        exit(1);
    }

    int i = 0;
    //while (fscanf(fp, "%lf %lf %lf", &x[i], &y[i], &targets[i]) != EOF)
    while (fscanf(fp, "%lf %lf %lf", &(x->elements[i]), &(y->elements[i]), &(targets->elements[i])) != EOF)
        i++;

    fclose(fp);

    fprintf(stdout, "load_data: loaded %d examples\n", i);
}

Model new_Model()
{
    Model model = (Model) malloc(sizeof(Model));
    model->weights = (double*) malloc(DIMENSIONS * sizeof(double));
    return model;
}

void initialize_model(Model model)
{
    for (int i = 0; i < DIMENSIONS; i++)
        model->weights[i] = (double) rand() / RAND_MAX;
}

static void sgd(Model model, double xcoord, double ycoord, double target)
{
    model->weights[2] += target * xcoord;
    model->weights[1] += target * ycoord;
    //weights[0] = weights[0];
    model->weights[0] += target * 1;
}

static int predict(Model model, double xcoord, double ycoord)
{
    double hypothesis = model->weights[2] * xcoord + model->weights[1] * ycoord + model->weights[0];
    return (hypothesis < 0) ? -1 : 1;
}

void fit_model(Model model, Data xcoords, Data ycoords, Data targets, int number_of_examples)
{
    double hypothesis, target;

    bool misclassified = true;
    while (misclassified) {
        misclassified = false;
        for (int i = 0; i < number_of_examples; i++) {
            hypothesis = predict(model, xcoords->elements[i], ycoords->elements[i]);
            target = targets->elements[i];
            if ((hypothesis > 0 && target > 0) || (hypothesis < 0 && target < 0)) // TODO Handle 0
                continue;
            sgd(model, xcoords->elements[i], ycoords->elements[i], target);  // Update weights using misclassified point
            misclassified = true;
        }
    }
}

void run_scoring_engine(Model model)
{
    double x, y;

    printf("Enter x: \n");
    scanf("%lf", &x);

    printf("Enter y: \n");
    scanf("%lf", &y);

    printf("Prediction = %d\n", predict(model, x, y));
}
