package edu.wm.cs.compiler.tools.generators.scanners;

import static java.nio.file.FileVisitResult.CONTINUE;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.charset.StandardCharsets;
import java.nio.file.FileVisitResult;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.SimpleFileVisitor;
import java.nio.file.attribute.BasicFileAttributes;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.StringJoiner;
import java.util.stream.Collectors;

import org.antlr.v4.runtime.ANTLRInputStream;
import org.antlr.v4.runtime.Token;
import org.apache.commons.cli.*;

public class JLexer extends SimpleFileVisitor<Path> { // Customize file visiting from SimpleFileVisitor

	private boolean normalize = false; // Assume normalization (token adjustment) should not occur unless explicitly told to do so
	private List<String> filesAnalyzed = new ArrayList<>(); // Initialize variable to store the names of analyzed files
	private Map<String, Integer> vocabulary = new HashMap<>(); // Initialize variable to hold token frequencies in a hash map
	
        // This method tokenizes java class files and writes the tokens to a new .lex file while preserving the line numbers that the tokens originally appeared in.
	@Override // Replace the implementation from parent class
	public FileVisitResult visitFile(Path path, BasicFileAttributes attr) throws IOException { // Attempt to visit file, otherwise throw input/output exception error
		if (!attr.isRegularFile() || !path.getFileName().toString().endsWith(".java") || attr.size() == 0L) // Filter out non-regular, non-regular, and non-java files
			return CONTINUE; // Signal to continue reading other files (so long as it is a normal .java file)
		
		InputStream inputStream = new FileInputStream(path.toAbsolutePath().toString()); // Create input stream to read file
		JavaLexer jLexer = new JavaLexer(new ANTLRInputStream(inputStream)); // Create custom tokenization object
		
		StringJoiner line = new StringJoiner(" "); // Create a string concatenator object to hold space-separated tokens
		List<String> lines = new ArrayList<>(); // Initialize list of tokenized lines
		
		int previousLine = 1; // Initialize tracker for previous line (starting with the first line)
		
		for (Token t = jLexer.nextToken(); t.getType() != Token.EOF; t = jLexer.nextToken()) { // Loop over file's tokens until the end of the file (EOF)
			if (t.getLine() == previousLine) { // Check if still tokenizing the stored line number "previous line"
				line.add(this.getText(t)); // Add token to string concatenator
			} else { // Otherwise, if the next token is on a new line, do the following
				lines.add(line.toString()); // Add previous line to saved array of tokenized lines
				line = new StringJoiner(" "); // Start new string concatenator to store tokens
				line.add(this.getText(t)); // Add the first token of the next line
				previousLine = t.getLine(); // Update previousLine to match the file reader's current location
			}
		}
		lines.add(line.toString()); // Flush last line. // Finalize last tokenized line after the loop
		lines.removeIf(String::isEmpty); // Remove first element (if necessary). // Dispose of empty lines
		
		Path lexPath = Paths.get(path.toAbsolutePath().toString().replaceAll(".java$", ".lex")); // Create lex file name by taking the original and replacing .java with .lex
		Files.write(lexPath, lines, StandardCharsets.UTF_8); // Write the tokenized lines to a new file with name lexPath

		this.filesAnalyzed.add(path.getFileName().toString()); // Save file to list of analyzed files
		
		return CONTINUE; // Signal to continue reading other files
	}

	private String getText(Token token) { // Method for converting a token into text
            String text = token.getText(); // Retrieve raw token text

		if (this.normalize) { // Convert text into custom token text when normalization is enabled
		switch (token.getType()) { // Handle cases for each type a token can be
			case JavaLexer.BooleanLiteral: // Boolean tokens
		 		text = "<BOOLEAN_LITERAL>"; // Change token's text to new custom form for
            			break; // Exit switch case
			case JavaLexer.CharacterLiteral: // Single character tokens
				text = "<CHARACTER_LITERAL>"; // Change token's text to new custom form for character literal strings
            			break; // Exit switch case
			case JavaLexer.FloatingPointLiteral: // Floating point number tokens
				text = "<FLOATING_POINT_LITERAL>"; // Change token's text to new custom form for floating point number literal strings
            			break; // Exit switch case
			case JavaLexer.IntegerLiteral: // Integer tokens
				text = "<INTEGER_LITERAL>"; // Change token's text to new custom form for integer literal strings
            			break; // Exit switch case
			case JavaLexer.NullLiteral: // Null tokens
				text = "<NULL_LITERAL>"; // Change token's text to new custom form for null literal strings
            			break; // Exit switch case
			case JavaLexer.StringLiteral: // String tokens
				text = "<STRING_LITERAL>"; // Change token's text to new custom form for string literal strings
            			break; // Exit switch case
			}
		}

		this.vocabulary.compute(text, (k, v) -> v == null ? 1 : v + 1); // Hash the token's text with key 'k' and value 'v' to the frequency hashmap. Add one to the frequency counter if the token has been encountered before or initialize a counter for that token if it is yet to be encountered.
                return text; // Return the (possibly normalized) text
	}

public static void main(String[] args) throws IOException, ParseException { // Main method to run lexer. Handles errors of corrupt file accessing and incorrect command parsing (for example forgetting to provide an input with option -i).
	Option input = Option.builder("i") // Assign user command prompt input option to variable
				 .longOpt("input") // Alternatively allow "input" to serve as the long name for i
				 .desc("TODO") // Unfinished description for input option
				 .required() // Forces input to be mandatory
				 .hasArg() // Forces input to have an argument
				 .argName("TODO") // Placeholder for the input argument
				 .build(); // Create input option
	Option output = Option.builder("o") // Assign user command prompt output option to variable
				  .longOpt("output") // Alternatively allow "output" to serve as the long name for o
				  .desc("TODO") // Unfinished description for output option
				  .required() // Forces output to be mandatory
				  .hasArg() // Forces output to have an argument
				  .argName("TODO") // Placeholder for the output argument
				  .build(); // Create output option
	Option version = Option.builder("v") // Assign user command prompt version option to variable
				   .longOpt("version") // Alternatively allow "version" to serve as the long name for v
				   .desc("TODO") // Unfinished description for version option
				   .required() // Forces version to be mandatory
				   .hasArg() // Forces version to have an argument
				   .argName("TODO") // Placeholder for the version argument
				   .build(); // Create version option
	Options options = new Options(); // Initialize options composite object to centralize all options created above
	options.addOption(input); // Save input to options
	options.addOption(output); // Save output to options
	options.addOption(version); // Save version to options
	options.addOption("n", "normalize", false, "TODO"); // Add optional option to normalize tokens

	CommandLineParser parser = new DefaultParser(); // Initialize parser to read the command line
	CommandLine cmd; // Initialize cmd to store parsed command line arguments
	try { // Attempt to parse the command line arguments
		cmd = parser.parse(options, args); // Parse the command line input to match the options created above
	} catch (ParseException e) { // If an error occured in parsing (such as a typo or a missed option in the command line) then throw error
		HelpFormatter formatter = new HelpFormatter(); // Create helpful error handler
		formatter.printHelp("java -jar path/to/jlexer.jar", options, true); // Provide error information
		throw e; // Throw error to end program
	}

        JLexer jLexer = new JLexer(); // Create lexer object to convert java source code into tokenized .lex files

		if (cmd.hasOption("n")) // Check if the user chose from the command line to normalize tokens
			jLexer.normalize = true; // Set normalization of tokens to true

		Files.walkFileTree(Paths.get(cmd.getOptionValue("i")), jLexer); // Visits files recursively within the given path from the -i input and lexes the files with the jLexer object

		String out = cmd.getOptionValue("o") + File.separator + cmd.getOptionValue("v"); // Create output path name given a name from -o, a separation value, and the version number

		Path log = Paths.get(out + ".log"); // Assign a log path to track command output from file and lexing operations
		Files.createDirectories(log.getParent()); // Create required directory for the log file (if it does not exist yet)
		Files.write(log, jLexer.filesAnalyzed, StandardCharsets.UTF_8); // Write the UTF-8 encoded file names of the analyzed files to the log file

		Path vocab = Paths.get(out + ".vocab"); // Assign token frequency file path
		Files.createDirectories(vocab.getParent()); // Create required directory for the token frequency file
		List<String> histogram = jLexer.vocabulary.entrySet().stream() // Use a stream to parse the mapped key/value pairs to strings to store in the frequency file
			.sorted(Map.Entry.comparingByValue()) // Sorts the keys from highest frequency to lowest frequency
			.map(Object::toString) // Convert key to string for readability
			.collect(Collectors.toList()); // Form a list out of the vocabulary entries
		Files.write(vocab, histogram, StandardCharsets.UTF_8); // Write the UTF-8 encoded histogram of token frequencies to the vocab file
	}

}
