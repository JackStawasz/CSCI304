package edu.wm.cs.cs301.sudoku;

import javax.swing.*;
import edu.wm.cs.cs301.sudoku.model.SudokuPuzzle;
import edu.wm.cs.cs301.sudoku.view.SudokuFrame;

/**
 * Run the GUI Sudoku program.
 *
 * @author Jack Stawasz
 */
public class Main implements Runnable {

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Main());
    }

    @Override
    public void run() {
        new SudokuFrame(new SudokuPuzzle());
    }
}