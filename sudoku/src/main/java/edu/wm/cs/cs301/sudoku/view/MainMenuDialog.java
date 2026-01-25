package edu.wm.cs.cs301.sudoku.view;

import edu.wm.cs.cs301.sudoku.model.SudokuPuzzle;

/**
 * Menu menu accessed from menubar.
 * See TitleScreenDialog for implementation.
 */
public class MainMenuDialog extends TitleScreenDialog {

    public MainMenuDialog(SudokuFrame view, SudokuPuzzle model) {
        super(view, model, "GUI Sudoku", true);
    }
}
