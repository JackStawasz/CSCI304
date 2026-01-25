package edu.wm.cs.cs301.sudoku.model;

import java.util.Random;

/**
 * The model containing the logic for creating Sudoku puzzles.
 * Provides the current game state, the solution, and the original
 * puzzle. This code has been reused and modified from Software
 * Development Spring 2025 project 1.
 * @author Jack Stawasz
 */
public class SudokuPuzzle {
    private static final int NUM_ROWS = 9;
    private static final int NUM_COLS = 9;
    private final int[] numberList = {1,2,3,4,5,6,7,8,9}; // Valid values in the grid
    private static final Random rand = new Random();

    private int selectRow;
    private int selectCol;

    // The current version of the puzzle including valid player moves
    private final int[][] current = new int[NUM_ROWS][NUM_COLS];

    // The solution to the current puzzle
    private final int[][] solution = new int[NUM_ROWS][NUM_COLS];

    // The starting puzzle given to the player
    private final int[][] clueGrid = new int[NUM_ROWS][NUM_COLS];

    public SudokuPuzzle() {
        initialize();
    }

    /**
     * Psuedo-constructor.
     * Allows public access to reset the puzzle.
     */
    public void initialize() {
        resetPuzzle();
        fillGrid();
        copyGridValues(current, solution); // Save solution
        removeClues();
        copyGridValues(current, clueGrid); // Save starting puzzle
    }

    private void resetPuzzle() {
        for (int i=0; i<NUM_ROWS; i++) {
            for (int j=0; j<NUM_ROWS; j++) {
                this.current[i][j] = 0;
                this.solution[i][j] = 0;
                this.clueGrid[i][j] = 0;
            }
        }
    }

    /**
     * Place value in current at row/col coordinate
     */
    public void setValue(int value) {current[selectRow][selectCol] = value;}

    /**
     * Check if value is not already in row/col/square
     */
    private boolean isValidValue(int[][] grid, int row, int col, int value) {
        // Search in row
        for (int element : grid[row]) {
            if (element == value) {
                return false;
            }
        }
        // Search in column
        for (int i=0; i < NUM_ROWS; i++) {
            if (grid[i][col] == value) {
                return false;
            }
        }
        // Search in 3x3 square
        int firstRow = row - (row % 3);
        int firstCol = col - (col % 3);
        for (int i=0; i < 3; i++) {
            for (int j=0; j<3; j++) {
                if (grid[firstRow + i][firstCol + j] == value) {
                    return false;
                }
            }
        }
        // If all tests pass, value is valid for the row/col pair
        return true;
    }

    /**
     * Return true if grid is full
     */
    public boolean isGridFull(int[][] grid) {
        // Search each row/col of current puzzle
        for(int row=0; row < NUM_ROWS; row++) {
            for(int col=0; col < NUM_COLS; col++) {
                if(grid[row][col] == 0) {
                    return false; // An empty space is found
                }
            }
        }
        return true; // The grid is full
    }

    /**
     * Create initially solved grid
     */
    public boolean fillGrid() {
        // Scan each cell for an empty space
        for (int row=0; row < NUM_ROWS; row++) {
            for (int col=0; col < NUM_COLS; col++) {
                if (current[row][col] == 0) {
                    shuffle(numberList); // Randomize the order of attempted value insertions
                    for (int value : numberList) { // Try inserting every possible value
                        if (isValidValue(current, row, col, value)) {
                            current[row][col] = value; // Assign testing value
                            if (isGridFull(current)) {
                                return true; // Grid is full
                            } else if (fillGrid()) { // See if this value allows for a full solution
                                return true; // Value worked --> use value
                            }
                            current[row][col] = 0; // Value didn't work --> backtrack value
                        }
                    }
                    return false; // Space has no valid value --> backtrack space
                }
            }
        }
        return true; // Grid is full
    }

    /**
     * Count solutions for a copy of the current grid
     */
    private boolean solveCopy(int[][] copyGrid, int[] solutionCount) {
        for (int row=0; row < NUM_ROWS; row++) {
            for (int col=0; col < NUM_COLS; col++) {
                if (copyGrid[row][col] == 0) {
                    for (int value=1; value <= 9; value++) {
                        if (isValidValue(copyGrid, row, col, value)) {
                            copyGrid[row][col] = value;
                            if (isGridFull(copyGrid)) {
                                solutionCount[0]++; // Solution found
                                if (solutionCount[0] > 1) {return false;}
                            } else if (solveCopy(copyGrid, solutionCount)) {
                                return true;
                            }
                            copyGrid[row][col] = 0; // Value didn't work --> backtrack value
                        }
                    }
                    return false; // Space has no valid value --> backtrack space
                }
            }
        }
        return true; // Grid is solved
    }

    /**
     * Add empty spaces to starting grid
     * (otherwise puzzle would already be solved)
     */
    public void removeClues() {
        int attempts = 20; // higher attempts makes more difficult puzzle
        int minEmptyCount = 30; // minimum empty spaces
        int emptyCount = 0;

        // Remove values that leave only 1 valid solution
        while (attempts > 0 || emptyCount < minEmptyCount) {
            int[] solutionCount = {0}; // Reset count before attempted removal

            // Find a random non-empty space
            int row = rand.nextInt(9);
            int col = rand.nextInt(9);
            while (current[row][col] == 0) {
                row = rand.nextInt(9);
                col = rand.nextInt(9);
            }
            int backup = current[row][col]; // Save removed value
            current[row][col] = 0; // Remove random value

            // Trigger solving on duplicate grid
            int[][] copyGrid = new int[NUM_ROWS][NUM_COLS];
            copyGridValues(current, copyGrid);
            solveCopy(copyGrid, solutionCount);
            if (solutionCount[0] != 1) { // Multiple solutions found --> removal failed
                current[row][col] = backup; // Reset original value
                attempts--; // Record failed removal
            } else {
                emptyCount++; // Successful removal --> new empty space
            }
        }
    }

    /**
     * (Util) Copy 2D array values to another 2D array
     * @param fromGrid input
     * @param toGrid target
     */
    private void copyGridValues(int[][] fromGrid, int[][] toGrid) {
        for (int row=0; row < NUM_ROWS; row++) {
            System.arraycopy(fromGrid[row], 0, toGrid[row], 0, NUM_COLS);
        }
    }

    /**
     * (Util) Randomize element positions for 1D array
     */
    private static void shuffle(int[] arr) {
        for (int i=0; i < arr.length; i++) { // Make n=array.length swaps
            int swapIndex = rand.nextInt(i + 1);
            int temp = arr[i];
            arr[i] = arr[swapIndex];
            arr[swapIndex] = temp;
        }
    }

    public int[][] getCurrent() {return current;}
    public int[][] getClueGrid() {return clueGrid;}
    public int[][] getSolution() {return solution;}

    public int getNumRows() {return NUM_ROWS;}
    public int getNumCols() {return NUM_COLS;}

    public void setSelectRow(int selectRow) {this.selectRow = selectRow;}
    public void setSelectCol(int selectCol) {this.selectCol = selectCol;}
    public int getSelectRow() {return selectRow;}
    public int getSelectCol() {return selectCol;}
    public boolean isValidSelectValue(int value) {return isValidValue(this.current, selectRow, selectCol, value);}
}
