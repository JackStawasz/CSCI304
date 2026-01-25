package edu.wm.cs.cs301.sudoku.controller;

import edu.wm.cs.cs301.sudoku.model.SudokuPuzzle;
import edu.wm.cs.cs301.sudoku.view.SudokuFrame;
import edu.wm.cs.cs301.sudoku.view.SudokuGridPanel;

import javax.swing.*;
import java.awt.event.ActionEvent;

/**
 * Actions for shifting selection square by one vertical/horizontal
 * square or to set selection to a specific button in the grid.
 * @author Jack Stawasz
 */
public class SelectionSquareAction extends AbstractAction {

    private final SudokuFrame view;
    private final SudokuPuzzle model;
    private final SudokuGridPanel grid;

    private final String direction;

    /**
     * Action for moving the selection square.
     * @param direction the shift (up, down, left, right)
     */
    public SelectionSquareAction(SudokuFrame view, SudokuPuzzle model, SudokuGridPanel grid, String direction) {
        this.view = view;
        this.model = model;
        this.grid = grid;
        this.direction = direction;
    }

    /**
     * Action for setting the selection to a target button.
     */
    public SelectionSquareAction(SudokuFrame view, SudokuPuzzle model, SudokuGridPanel grid) {
        this.view = view;
        this.model = model;
        this.grid = grid;
        this.direction = null;
    }

    @Override
    public void actionPerformed(ActionEvent event) {
        //String text = (String) getValue(Action.ACTION_COMMAND_KEY);
        JButton button = (JButton) event.getSource();
        String text;
        if(direction != null) {
            text = direction;
        } else {
            text = button.getActionCommand();
        }

        switch (text) {
            case "Up" -> grid.moveSelectionSquare(0, 1);
            case "Down" -> grid.moveSelectionSquare(0, -1);
            case "Left" -> grid.moveSelectionSquare(-1, 0);
            case "Right" -> grid.moveSelectionSquare(1, 0);
            case "Press" -> {
                grid.changeSelectionSquare(button);
                view.repaintGridPanel();
            }
            default -> {
                System.out.println("Failed to match input: " + text);
            }
        }
    }
}
