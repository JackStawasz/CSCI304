package edu.wm.cs.cs301.sudoku.controller;

import edu.wm.cs.cs301.sudoku.model.SudokuPuzzle;
import edu.wm.cs.cs301.sudoku.view.CongratsDialog;
import edu.wm.cs.cs301.sudoku.view.SudokuFrame;

import javax.swing.*;
import java.awt.event.ActionEvent;

/**
 * Actions for entering selection number 1-9, entering
 * selection to model, and deleting selection from model.
 * @author Jack Stawasz
 */
public class KeyboardButtonAction extends AbstractAction {

    private final SudokuFrame view;
    private final SudokuPuzzle model;

    public KeyboardButtonAction(SudokuFrame view, SudokuPuzzle model) {
        this.view = view;
        this.model = model;
    }

    @Override
    public void actionPerformed(ActionEvent event) {
        JButton button = (JButton) event.getSource();
        String text = button.getActionCommand();

        boolean isNotClueGrid = model.getClueGrid()[model.getSelectRow()][model.getSelectCol()] == 0;

        if (text.equals("Enter")) {
            int value = Integer.parseInt(view.getSelectionValue());
            boolean isValid = model.isValidSelectValue(value);

            // Check to insert value to model and repaint grid
            if (isValid && isNotClueGrid) {
                model.setValue(value);
                view.repaintGridPanel();
            } else {
                view.setIncorrectSelection();
            }

            // Check for completed puzzle to end game
            // (only one solution exists so a full grid is a completed grid)
            if (model.isGridFull(model.getCurrent())) {
                new CongratsDialog(view, model);
            }
        } else if (text.equals("Backspace") || text.equals("Delete")) {
            if (isNotClueGrid) {
                model.setValue(0);
                view.repaintGridPanel();
            } else {
                view.setIncorrectSelection();
            }
        } else if (text.matches("[1-9]")) {
            if (isNotClueGrid) {
                int value = Integer.parseInt(text);
                view.setSelectionValue(Integer.toString(value));
            } else {
                view.setIncorrectSelection();
            }
        } else {
            System.out.println("Failed to match input");
        }
    }
}
