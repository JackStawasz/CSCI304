package edu.wm.cs.cs301.sudoku.view;

import edu.wm.cs.cs301.sudoku.model.SudokuPuzzle;

import javax.swing.*;
import java.awt.*;

/**
 * A pop-up window with instructions for both Sudoku
 * puzzle completion conditions and client-GUI interactions.
 * @author Jack Stawasz
 */
public class InstructionsDialog extends JDialog {

    private final SudokuFrame view;
    private final SudokuPuzzle model;

    private final static int TITLE_SIZE = 60;
    private final static int TEXT_SIZE = 20;

    public InstructionsDialog(SudokuFrame view, SudokuPuzzle model) {
        super(view.getFrame(), "Instructions", true);
        this.view = view;
        this.model = model;

        initializeInstructionsScreen();
        pack();
        setLocationRelativeTo(view.getFrame());

        setVisible(true);
    }

    /**
     * Psuedo-constructor.
     * Create the screen to hold components vertically.
     */
    private void initializeInstructionsScreen() {
        JPanel mainPanel = new JPanel();
        mainPanel.setLayout(new BoxLayout(mainPanel, BoxLayout.Y_AXIS));
        mainPanel.setBorder(BorderFactory.createEmptyBorder(0, 5, 5, 5));

        mainPanel.add(createTitlePanel());
        mainPanel.add(createSudokuInfoPanel());
        mainPanel.add(createWhiteSpace(20));
        mainPanel.add(createGUIInfoPanel());

        add(mainPanel);
    }

    /**
     * Create Instructions title.
     */
    private JPanel createTitlePanel() {
        JPanel panel = new JPanel(new FlowLayout());
        panel.setBorder(BorderFactory.createEmptyBorder(0, 5, 5, 5));

        JLabel label = new JLabel("Instructions");
        label.setFont(new Font("Dialog", Font.BOLD, TITLE_SIZE));
        panel.add(label);

        return panel;
    }

    /**
     * Display instructions for how to solve
     * a Sudoku puzzle.
     */
    private JPanel createSudokuInfoPanel() {
        JPanel panel = new JPanel();
        panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
        panel.setBorder(BorderFactory.createEmptyBorder(0, 5, 5, 5));

        JLabel[] labels = new JLabel[2];
        labels[0] = new JLabel("Complete the puzzle by filling the 9x9 grid with");
        labels[1] = new JLabel("values 1-9 exactly once per row, column, and 3x3 square.");

        for (JLabel label : labels) {
            label.setFont(new Font("Dialog", Font.PLAIN, TEXT_SIZE));
            panel.add(label);
        }

        return panel;
    }

    /**
     * Display instructions for how to use
     * GUI software.
     */
    private JPanel createGUIInfoPanel() {
        JPanel panel = new JPanel();
        panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
        panel.setBorder(BorderFactory.createEmptyBorder(0, 5, 5, 5));

        JLabel[] labels = new JLabel[6];
        labels[0] = new JLabel("For this GUI program, grid squares are selected by either clicking");
        labels[1] = new JLabel("on them with the mouse or by moving the selection square with either");
        labels[2] = new JLabel("the arrow or wasd keys. You may alter the selection with the on-screen");
        labels[3] = new JLabel("numbers or the physical keyboard numbers 1-9. You must hit");
        labels[4] = new JLabel("enter on the selection for the game to save your selection before");
        labels[5] = new JLabel("moving onto the next selection.");

        for (JLabel label : labels) {
            label.setFont(new Font("Dialog", Font.PLAIN, TEXT_SIZE));
            panel.add(label);
        }

        return panel;
    }

    /**
     * Insert spacing of variable height.
     */
    private Box createWhiteSpace(int boxHeight) {
        Box box = Box.createVerticalBox();
        box.add(Box.createRigidArea(new Dimension(0, boxHeight))); // adds 400px vertical space

        return box;
    }
}
