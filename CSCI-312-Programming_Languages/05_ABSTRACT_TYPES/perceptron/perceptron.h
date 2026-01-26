#ifndef PERCEPTRON_H
#define PERCEPTRON_H
#define DIMENSIONS 3

typedef struct data *Data;
typedef struct model *Model;

// Building
Data new_Data(int number_of_examples);
Model new_Model();
void load_data(char *fname, Data xcoords, Data ycoords, Data targets);
void initialize_model(Model model);

// Training
void fit_model(Model model, Data xcoords, Data ycoords, Data targets, int number_of_examples);

// Testing

// Scoring
void run_scoring_engine(Model model);

#endif
