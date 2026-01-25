package edu.wm.cs.cs301.sudoku.view;

import edu.wm.cs.cs301.sudoku.model.SudokuPuzzle;

import javax.swing.*;
import java.awt.*;
import java.awt.event.KeyEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

/**
 * Main view for executable program.
 * Initializes all visual components.
 * @author Jack Stawasz
 */
public class SudokuFrame {

    private final SudokuPuzzle model;

    private final JFrame frame;

    private final SudokuGridPanel gridPanel;
    private final KeyboardPanel keyboardPanel;

    public SudokuFrame(SudokuPuzzle model) {
        this.model = model;
        this.keyboardPanel = new KeyboardPanel(this, model);
        int width = keyboardPanel.getPanel().getPreferredSize().width;
        this.gridPanel = new SudokuGridPanel(this, model, width);
        this.frame = createAndShowGUI();
    }

    /**
     * Create the frame (software window) for the program
     */
    private JFrame createAndShowGUI() {
        JFrame frame = new JFrame("Sudoku");
        frame.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);

        ImageIcon icon = new ImageIcon(getClass().getResource("/SudokuLogo.png"));
        Image iconImage = icon.getImage().getScaledInstance(128, 128, Image.SCALE_SMOOTH);
        frame.setIconImage(iconImage);

        frame.setResizable(false);
        frame.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent event) {
                shutdown();
            }
        });

        // Create dummy panel for box layout to work
        JPanel framePanel = new JPanel();
        framePanel.setLayout(new BoxLayout(framePanel, BoxLayout.Y_AXIS));
        // Toolbar
        JToolBar toolBar = createToolBar();
        JPanel toolBarPanel = new JPanel(new FlowLayout(FlowLayout.LEFT));
        toolBarPanel.add(toolBar);
        framePanel.add(toolBarPanel);
        // Title, grid, keyboard
        framePanel.add(createTitlePanel());
        framePanel.add(gridPanel);
        framePanel.add(keyboardPanel.getPanel());
        frame.add(framePanel);

        frame.pack();
        frame.setLocationByPlatform(true);
        frame.setVisible(true);
        gridPanel.requestFocus(); // Allows arrow keys to move selection square

        return frame;
    }

    /**
     * Create bar at the top of the screen.
     * Analogous to menubar except menu items do not
     * have drop-downs and are instead buttons.
     */
    private JToolBar createToolBar() {
        JToolBar toolBar = new JToolBar();

        JButton mainMenu = new JButton("Main Menu");
        mainMenu.addActionListener(e -> {new MainMenuDialog(this, model);});
        toolBar.add(mainMenu);

        JButton instructionsMenu = new JButton("Instructions");
        instructionsMenu.addActionListener(e -> {new InstructionsDialog(this, model);});
        toolBar.add(instructionsMenu);

        return toolBar;
    }

    /**
     * Title above the playing space.
     * (In case the user forgot what game they were playing)
     */
    private JPanel createTitlePanel() {
        JPanel panel = new JPanel(new FlowLayout());
        panel.setBorder(BorderFactory.createEmptyBorder(0, 5, 5, 5));

        // Close game after hitting escape key
        InputMap inputMap = panel.getInputMap(JPanel.WHEN_IN_FOCUSED_WINDOW);
        inputMap.put(KeyStroke.getKeyStroke(KeyEvent.VK_ESCAPE, 0), "cancelAction");

        JLabel label = new JLabel("Sudoku");
        label.setFont(new Font("Dialog", Font.BOLD, 80));
        panel.add(label);

        return panel;
    }

    /**
     * Custom method for close-game action.
     * Dispose frame and exit the system.
     */
    public void shutdown() {
        frame.dispose();
        System.exit(0);
    }

    /**
     * Reset gridPanel back to the values contained in the model.
     */
    public void repaintGridPanel() { gridPanel.updateButtonsText(); }

    public JFrame getFrame() {
        return frame;
    }

    public void setSelectionValue(String value) {
        gridPanel.setSelectionValue(value);
    }
    public String getSelectionValue() {
        return gridPanel.getSelectionValue();
    }
    public void setIncorrectSelection() {
        gridPanel.incorrectSelection();
    }
}
