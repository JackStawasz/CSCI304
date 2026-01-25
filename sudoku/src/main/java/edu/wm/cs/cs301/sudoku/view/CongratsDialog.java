package edu.wm.cs.cs301.sudoku.view;

import edu.wm.cs.cs301.sudoku.model.SudokuPuzzle;

/**
 * Award message for puzzle completion.
 * See TitleScreenDialog for implementation.
 */
public class CongratsDialog extends TitleScreenDialog {

    public CongratsDialog(SudokuFrame view, SudokuPuzzle model) {
        super(view, model, "Congratulations!!!", false);
    }
}
