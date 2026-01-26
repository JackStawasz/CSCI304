package perceptron;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;
import java.util.Scanner;

class Example {
  List<Double> input = new ArrayList<Double>();
  Double target;
}

class Data {
  List<Example> examples = new ArrayList<Example>();
  int number_of_features = 0;

  Data(String fname) throws FileNotFoundException {
    Scanner scanner = new Scanner(new File(fname));
    while (scanner.hasNextLine()) {
      List<String> line = Arrays.asList(scanner.nextLine().trim().split(" "));
      if (number_of_features == 0) {
        number_of_features = line.size() - 1;
      }
      Example example = new Example();
      example.input.add(1.0);
      for (int i = 0; i < number_of_features; i++) {
        example.input.add(Double.parseDouble(line.get(i)));
      }
      example.target = Double.parseDouble(line.get(number_of_features));
      System.out.println(example.input);
      examples.add(example);
    }
  }

  public static void main(String[] args) throws FileNotFoundException {
    Data data = new Data(args[0]);
    System.out.println("Loaded " + data.examples.size() + " examples");
  }
}
