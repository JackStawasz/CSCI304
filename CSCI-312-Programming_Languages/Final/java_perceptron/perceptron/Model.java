package perceptron;
import perceptron.Data;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

class Weight {
    private double value;
    Weight(double randVal) {
        this.value = randVal;
    }

    public void addToValue(double addWeight) {
        this.value += addWeight;
    }
    public double getValue() {
        return this.value;
    }
}

class Model {
    List<Weight> weights = new ArrayList<Weight>();
    Double dimensionality = 0.0;

    Model(Data data) {
        dimensionality = data.number_of_features + 1.0;
        for (int i = 0; i < dimensionality; i++) {
            weights.add(new Weight(Math.random()));
        }
    }

    void sgd(Example example) {
        for (int i = 0; i < weights.size(); i++) {
            weights.get(i).addToValue(example.target * example.input.get(i));
        }
    }

    void fit(Data data) {
        double hypothesis, target;
        int example_count = data.examples.size();

        boolean misclassified = true;
        while (misclassified) {
            misclassified = false;
            for (int row=0; row<example_count; row++) {
                hypothesis = predict(data.examples.get(row));
                target = data.examples.get(row).target;
                if ((hypothesis > 0 && target > 0) || (hypothesis < 0 && target < 0) || target==0) {
                    continue; // Skip over correctly classified points
                } else {
                    sgd(data.examples.get(row)); // Update weights using misclassified point
                    misclassified = true; // Trigger recheck on other points (prevent regression)
                }
            }
        }
        // Debug print each weight
        //for (Weight weight : weights) {
        //    System.out.println(weight.getValue());
        //}
    }

    int predict(Example example) {
        double hypothesis = 0.0;
        for (int i = 0; i < weights.size(); i++) {
            hypothesis += weights.get(i).getValue() * example.input.get(i);
        }
        return (hypothesis < 0) ? -1 : 1;
    }

    void evaluate(Data data) {
        double hypothesis, target;
        int example_count = data.examples.size();
        int correct_count = 0;
        
        for (int row=0; row<example_count; row++) {
            hypothesis = predict(data.examples.get(row));
            target = data.examples.get(row).target;
            if ((hypothesis > 0 && target > 0) || (hypothesis < 0 && target < 0) || target==0) {
                correct_count += 1;
            } else {
                continue;
            }
        }
        double percent_correct = 100*((double)correct_count / example_count);
        System.out.println("Testing Results: model is " + percent_correct + "% correct.");
    }

    void runScoringEngine() {
        double x, y;
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter x: ");
        x = scanner.nextDouble();

        System.out.println("Enter y: ");
        y = scanner.nextDouble();

        // Save x and y to a feature vector
        Example feature = new Example();
        feature.input.add(1.0); // Bias term
        feature.input.add(x);
        feature.input.add(y);

        System.out.println("Prediction = " + predict(feature));
    }
}

