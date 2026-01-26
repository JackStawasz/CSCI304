#ifndef PERCEPTRON_H
#define PERCEPTRON_H

typedef struct data *Data;
typedef struct model *Model;
typedef struct shape *Shape;

// Building
Data new_Data(const char *fname);
Model new_Model(const Data data);

// Training
void fit_model(Model model, Data data);

// Testing
void evaluate_model(Model model, Data data);

// Scoring
void run_scoring_engine(const Model model);

// Memory freeing
void delete_Data(Data data);
void delete_Model(Model model);

#endif
