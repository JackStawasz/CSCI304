package edu.wm.cs.cs301.sudoku.view;

import edu.wm.cs.cs301.sudoku.controller.SelectionSquareAction;
import edu.wm.cs.cs301.sudoku.model.SudokuPuzzle;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.KeyEvent;

import javax.swing.*;

/**
 * The visual playing grid to display the SudokuPuzzle model.
 * Creates the grid only once; new games only update the grid.
 * Holds selection square logic and listeners.
 * @author Jack Stawasz
 */
public class SudokuGridPanel extends JPanel {

    private final int squareWidth;
    private final Color BUTTON_BORDER_COLOR = Color.GRAY;

    private final JButton[][] buttons;
    private final int numRows;
    private final int numCols;

    private final SudokuPuzzle model;
    private final SudokuFrame view;

    private JButton selectionSquare = null;
    private final SelectionSquareAction action;
    private static final int SELECTION_THICKNESS = 3;

    public SudokuGridPanel(SudokuFrame view, SudokuPuzzle model, int width) {
        // Assign model info
        this.model = model;
        this.view = view;
        this.numRows = model.getNumRows();
        this.numCols = model.getNumCols();
        this.buttons = new JButton[numRows][numCols];

        // Set grid sizes
        this.squareWidth = 44;
        Insets insets = new Insets(0, 0, 0, 0);
        int rowWidth = (squareWidth + insets.right) * numCols;
        int height = (squareWidth + insets.bottom) * numRows;
        this.setPreferredSize(new Dimension(width, height));

        // Create grid
        JLayeredPane gridPanel = createGrid(rowWidth, height);
        this.setLayout(new FlowLayout(FlowLayout.CENTER, 0, 0));
        this.add(gridPanel);

        // Selection square
        this.action = new SelectionSquareAction(view, model, this);
        this.setFocusTraversalKeysEnabled(false);
        changeSelectionSquare(buttons[0][0]);
        selectionListeners();
    }

    /**
     * Creates the grid object containing the visual of the
     * SudokuPuzzle model. The layered pane type is for overlaying the
     * 9x9 and 3x3 squares.
     */
    private JLayeredPane createGrid(int width, int height) {
        JLayeredPane gridPanel = new JLayeredPane();
        gridPanel.setPreferredSize(new Dimension(width, height));

        // Create buttons
        JPanel buttonGridPanel = new JPanel();
        buttonGridPanel.setLayout(new GridLayout(numRows, numCols));
        buttonGridPanel.setBounds(0,0,width, height);
        for (int row = 0; row < numRows; row++) {
            for (int col = 0; col < numCols; col++) {
                JButton button = createSquare(row, col);
                buttons[row][col] = button;
                button.putClientProperty("row", row);
                button.putClientProperty("col", col);
                buttonGridPanel.add(buttons[row][col]);
            }
        }
        updateButtonsText();
        gridPanel.add(buttonGridPanel, JLayeredPane.DEFAULT_LAYER);

        // Create 9x9 Border
        JPanel nineByNineOutline = new JPanel();
        nineByNineOutline.setBorder(BorderFactory.createLineBorder(Color.BLACK, 6));
        nineByNineOutline.setOpaque(false);
        nineByNineOutline.setBounds(0, 0, width, height);
        gridPanel.add(nineByNineOutline, JLayeredPane.MODAL_LAYER);

        // Create nine 3x3 borders
        int boxWidth = width / 3;
        int boxHeight = height / 3;
        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                JPanel threeByThreeOutline = new JPanel();
                threeByThreeOutline.setBorder(BorderFactory.createLineBorder(new Color(80, 70, 70), 2)); // Dark Gray RGB
                threeByThreeOutline.setOpaque(false); // So we can see what's underneath
                threeByThreeOutline.setBounds(j * boxWidth, i * boxHeight, boxWidth, boxHeight);
                gridPanel.add(threeByThreeOutline, JLayeredPane.PALETTE_LAYER);
            }
        }

        return gridPanel;
    }

    /**
     * Creates a square button at the specified row and column.
     * Each new button holds its own action listener so that
     * a button press selects that button.
     */
    private JButton createSquare(int row, int col) {
        JButton button = new JButton();

        // Edit button settings
        button.setPreferredSize(new Dimension(squareWidth, squareWidth));
        button.setFont(new Font("Arial", Font.BOLD, 18));
        button.setBackground(new Color(219, 219, 219)); // Light Gray RGB
        button.setForeground(Color.BLACK); // AKA text color
        button.setBorder(BorderFactory.createLineBorder(BUTTON_BORDER_COLOR));

        // Add action listener
        String text = "Press";
        button.setActionCommand(text);
        button.addActionListener(e -> {
            action.actionPerformed(new ActionEvent(button, ActionEvent.ACTION_PERFORMED, text));
            model.setSelectRow(row);
            model.setSelectCol(col);
        });

        return button;
    }

    /**
     * Reset all numbers in the grid to match the model.
     * This is used for initialization and entering a
     * selected value.
     */
    public void updateButtonsText() {
        for (int row = 0; row < numRows; row++) {
            for (int col = 0; col < numCols; col++) {
                updateButtonText(row, col);
            }
        }
        repaint();
        revalidate();
    }

    /**
     * Reset a grid square to match the model.
     * Acts as a repaint method to reset view to the model.
     */
    private void updateButtonText(int row, int col) {
        int[][] sudokuGrid = model.getCurrent();
        int squareNumber = sudokuGrid[row][col];

        // Only print nonzero grid contents
        String buttonText;
        if (squareNumber == 0) {
            buttonText = "";
        } else {
            buttonText = Integer.toString(squareNumber);
        }
        buttons[row][col].setText(buttonText);
        buttons[row][col].setForeground(Color.BLACK);
    }

    /**
     * Move selection square to a set button.
     */
    public void changeSelectionSquare(JButton button) {
        // Reset old selection
        if (selectionSquare != null) {
            updateButtonText(model.getSelectRow(), model.getSelectCol());
            this.selectionSquare.setBorder(BorderFactory.createLineBorder(BUTTON_BORDER_COLOR));
        }

        // Set new selection
        this.selectionSquare = button;
        selectionSquare.setBorder(BorderFactory.createLineBorder(Color.BLUE, SELECTION_THICKNESS));
    }

    /**
     * Shift selection square x units horizontally and
     * y units vertically.
     */
    public void moveSelectionSquare(int x, int y) {
        // Find current selection position
        int buttonRow = (int) selectionSquare.getClientProperty("row");
        int buttonCol = (int) selectionSquare.getClientProperty("col");

        // Prevent going out of bounds
        int newRow = buttonRow - y;
        int newCol = buttonCol + x;
        if (newRow >= 0 && newRow < numRows && newCol >= 0 && newCol < numCols) {
            changeSelectionSquare(buttons[newRow][newCol]);
            model.setSelectRow(newRow);
            model.setSelectCol(newCol);
        } else {
            // Index is out of bounds
            incorrectSelection();
        }
    }

    /**
     * Mark the selection square red for a brief period.
     */
    public void incorrectSelection() {
        int DELAY = 500; // Time that incorrect value turns red
        SwingUtilities.invokeLater(() -> {
                selectionSquare.setForeground(Color.RED); // Text color
                selectionSquare.setBorder(BorderFactory.createLineBorder(Color.RED, SELECTION_THICKNESS));
        });
        javax.swing.Timer timer = new javax.swing.Timer(DELAY, e -> {
            selectionSquare.setForeground(Color.BLACK); // Text color
            selectionSquare.setBorder(BorderFactory.createLineBorder(Color.BLUE, SELECTION_THICKNESS));
            view.repaintGridPanel();
        });
        timer.setRepeats(false);
        timer.start();
    }

    /**
     * Map wasd/arrow key selection movement to the
     * selection square controller action.
     */
    private void selectionListeners() {
        String[] directions = {"Up", "Down", "Left", "Right"};
        JButton button = buttons[0][0]; // Arbitrary button to hold actions
        button.requestFocus();
        InputMap inputMap = button.getInputMap(JButton.WHEN_IN_FOCUSED_WINDOW);
        ActionMap actionMap = button.getActionMap();

        for (String direction : directions) {
            // Identify keystroke and insert to inputMap
            KeyStroke keyStroke1;
            KeyStroke keyStroke2;
            switch (direction) {
                case "Up" -> {
                    keyStroke1 = KeyStroke.getKeyStroke(KeyEvent.VK_UP, 0);
                    keyStroke2 = KeyStroke.getKeyStroke(KeyEvent.VK_W, 0);
                }
                case "Down" -> {
                    keyStroke1 = KeyStroke.getKeyStroke(KeyEvent.VK_DOWN, 0);
                    keyStroke2 = KeyStroke.getKeyStroke(KeyEvent.VK_S, 0);
                }
                case "Left" -> {
                    keyStroke1 = KeyStroke.getKeyStroke(KeyEvent.VK_LEFT, 0);
                    keyStroke2 = KeyStroke.getKeyStroke(KeyEvent.VK_A, 0);
                }
                case "Right" -> {
                    keyStroke1 = KeyStroke.getKeyStroke(KeyEvent.VK_RIGHT, 0);
                    keyStroke2 = KeyStroke.getKeyStroke(KeyEvent.VK_D, 0);
                }
                default -> throw new IllegalStateException("Unexpected direction: " + direction);
            }
            String arrowKey = "arrow_" + direction;
            String wasdKey = "wasd_" + direction;
            inputMap.put(keyStroke1, arrowKey);
            inputMap.put(keyStroke2, wasdKey);

            // Place action into action map
            actionMap.put(arrowKey, new SelectionSquareAction(view, model, this, direction));
            actionMap.put(wasdKey, new SelectionSquareAction(view, model, this, direction));
        }
    }

    public void setSelectionValue(String value) {
        SwingUtilities.invokeLater(() -> {
            selectionSquare.setText(value);
            selectionSquare.setForeground(Color.BLUE);
        });
    }
    public String getSelectionValue() {
        return selectionSquare.getText();
    }
}

