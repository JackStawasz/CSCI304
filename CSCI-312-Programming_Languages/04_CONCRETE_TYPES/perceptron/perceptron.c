#include "perceptron.h"

void load_data(char *fname, double x[], double y[], double targets[])
{
    FILE *fp;

    if ((fp = fopen(fname, "r")) == NULL)  {
        fprintf(stderr, "load_data: can't open %s\n", fname);
        exit(1);
    }

    int i = 0;
    while (fscanf(fp, "%lf %lf %lf", &x[i], &y[i], &targets[i]) != EOF)
        i++;

    fclose(fp);

    fprintf(stdout, "load_data: loaded %d examples\n", i);
}

void initialize(double weights[])
{
    for (int i = 0; i < DIMENSIONS; i++)
        weights[i] = (double) rand() / RAND_MAX;
}

static void sgd(double weights[], double x, double y, double target)
{
    weights[2] += target * x;
    weights[1] += target * y;
    //weights[0] = weights[0];
    weights[0] += target * 1;
}

void fit(double weights[], double x[], double y[], double targets[], int number_of_examples)
{
    double hypothesis, target;

    bool misclassified = true;
    while (misclassified) {
        misclassified = false;
        for (int i = 0; i < number_of_examples; i++) {
            hypothesis = predict(weights, x[i], y[i]);
            target = targets[i];
            if ((hypothesis > 0 && target > 0) || (hypothesis < 0 && target < 0)) // TODO Handle 0
                continue;
            sgd(weights, x[i], y[i], target);  // Update weights using misclassified point
            misclassified = true;
        }
    }
}

int predict(double weights[], double x, double y)
{
    double hypothesis = weights[2] * x + weights[1] * y + weights[0];
    return (hypothesis < 0) ? -1 : 1;
}

void run_scoring_engine(double weights[])
{
    double x, y;

    printf("Enter x: \n");
    scanf("%lf", &x);

    printf("Enter y: \n");
    scanf("%lf", &y);

    printf("Prediction = %d\n", predict(weights, x, y));
}
