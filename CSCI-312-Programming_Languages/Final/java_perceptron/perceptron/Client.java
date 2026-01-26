package perceptron;

import java.io.FileNotFoundException;

class Client {
    public static void main(String[] args) {
        // usage: java Client train.dat test.dat

        if (args.length != 2) {
            System.out.println("Usage: java perceptron.Client <train_file> <test_file>");
            return;
        }
        String train_dat = args[0];
        String test_dat = args[1];

        try {
            // Building
            Data training_data = new Data(train_dat);
            Data testing_data = new Data(test_dat);
            Model model = new Model(training_data);

            // Training
            model.fit(training_data);

            // Testing
            model.evaluate(testing_data);

            // Scoring
            model.runScoringEngine();
        } catch (FileNotFoundException e) {
            System.err.println("One of the data files was not found: " + e.getMessage());
        }
    }
}

