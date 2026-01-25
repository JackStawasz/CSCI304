package edu.wm.cs.cs301.sudoku.view;

import edu.wm.cs.cs301.sudoku.model.SudokuPuzzle;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.KeyEvent;

/**
 * Implementation for title-screen-like objects.
 * Allows play again to create new puzzle and quit
 * to exit the program.
 * @author Jack Stawasz
 */
public abstract class TitleScreenDialog extends JDialog {

    private final ExitAction exitAction;
    private final NextAction nextAction;

    private final SudokuFrame view;
    private final SudokuPuzzle model;

    private final static int BUTTON_HEIGHT = 50;
    private final static int BUTTON_WIDTH = 250;

    private final String title;
    private final boolean hasAuthor;

    public TitleScreenDialog(SudokuFrame view, SudokuPuzzle model, String title, boolean hasAuthor) {
        super(view.getFrame(), "Main Menu", true);
        this.view = view;
        this.model = model;
        this.exitAction = new ExitAction();
        this.nextAction = new NextAction();
        this.title = title;
        this.hasAuthor = hasAuthor;

        initializeTitleScreen();
        pack();
        setLocationRelativeTo(view.getFrame());

        setVisible(true);
    }

    /**
     * Psuedo-constructor to organize screen components.
     */
    private void initializeTitleScreen() {
        // Add title, author, and buttons
        JPanel mainPanel = createMainPanel();
        Box whiteSpace = createWhiteSpace(100);
        JPanel buttonPanel = createButtonPanel();

        // Create dummy panel to hold components
        JPanel screenPanel = new JPanel();
        screenPanel.setLayout(new BoxLayout(screenPanel, BoxLayout.Y_AXIS));
        screenPanel.add(mainPanel);
        screenPanel.add(whiteSpace);
        screenPanel.add(buttonPanel);
        screenPanel.add(whiteSpace);

        add(screenPanel);
    }

    /**
     * The header of the title screen.
     * Optional author included.
     */
    private JPanel createMainPanel() {
        JPanel panel = new JPanel(new BorderLayout());
        panel.setBorder(BorderFactory.createEmptyBorder(0, 5, 5, 5));

        panel.add(createTitlePanel(), BorderLayout.NORTH);
        if (this.hasAuthor) {
            panel.add(createAuthorPanel(), BorderLayout.SOUTH);
        }

        return panel;
    }

    /**
     * Displays the title of the title screen.
     */
    private JPanel createTitlePanel() {
        JPanel panel = new JPanel(new FlowLayout());
        panel.setBorder(BorderFactory.createEmptyBorder(0, 5, 5, 5));

        JLabel label = new JLabel(this.title);
        label.setFont(new Font("Dialog", Font.BOLD, 80));
        panel.add(label);

        return panel;
    }

    /**
     * Displays the author underneath the title.
     */
    private JPanel createAuthorPanel() {
        JPanel panel = new JPanel(new FlowLayout());
        panel.setBorder(BorderFactory.createEmptyBorder(0, 5, 5, 5));

        JLabel label = new JLabel("by Jack Stawasz");
        label.setFont(new Font("Dialog", Font.ITALIC, 30));
        panel.add(label);

        return panel;
    }

    /**
     * Empty space to be inserted between components.
     */
    private Box createWhiteSpace(int boxHeight) {
        Box box = Box.createVerticalBox();
        box.add(Box.createRigidArea(new Dimension(0, boxHeight))); // adds 400px vertical space

        return box;
    }

    /**
     * Title screen buttons.
     * Contains play again and quit.
     */
    private JPanel createButtonPanel() {
        JPanel panel = new JPanel();
        panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
        panel.setBorder(BorderFactory.createEmptyBorder(0, 5, 5, 5));

        Box whiteSpace = createWhiteSpace(10);
        final Font textfont =  new Font("Dialog", Font.PLAIN, 30);

        InputMap inputMap = panel.getInputMap(JPanel.WHEN_IN_FOCUSED_WINDOW);
        inputMap.put(KeyStroke.getKeyStroke(KeyEvent.VK_ESCAPE, 0), "exitAction");
        inputMap.put(KeyStroke.getKeyStroke(KeyEvent.VK_ENTER, 0), "nextAction");
        ActionMap actionMap = panel.getActionMap();
        actionMap.put("nextAction", nextAction);
        actionMap.put("exitAction", exitAction);

        JButton playButton = new JButton("Play");
        playButton.addActionListener(nextAction);
        playButton.setAlignmentX(Component.CENTER_ALIGNMENT);
        // Set Appearance
        playButton.setMaximumSize(new Dimension(BUTTON_WIDTH, BUTTON_HEIGHT));
        playButton.setBackground(new Color(222, 220, 250)); // Light Blue RGB
        playButton.setBorder(BorderFactory.createLineBorder(new Color(170, 180, 240))); // Light(ish) blue RGB
        playButton.setForeground(Color.BLACK); // AKA text color
        playButton.setFont(textfont);

        JButton quitButton = new JButton("Quit");
        quitButton.addActionListener(exitAction);
        quitButton.setAlignmentX(Component.CENTER_ALIGNMENT);
        // Set Appearance
        quitButton.setMaximumSize(new Dimension(BUTTON_WIDTH, BUTTON_HEIGHT));
        quitButton.setBackground(new Color(222, 220, 250)); // Light Blue RGB
        quitButton.setBorder(BorderFactory.createLineBorder(new Color(170, 180, 240))); // Light(ish) blue RGB
        quitButton.setForeground(Color.BLACK); // AKA text color
        quitButton.setFont(textfont);

        panel.add(playButton);
        panel.add(whiteSpace);
        panel.add(quitButton);

        return panel;
    }

    /**
     * Close the program.
     */
    private class ExitAction extends AbstractAction {
        @Override
        public void actionPerformed(ActionEvent event) {
            dispose();
            view.shutdown();
        }
    }

    /**
     * Exit title window and create the next puzzle.
     */
    private class NextAction extends AbstractAction {
        @Override
        public void actionPerformed(ActionEvent event) {
            dispose();
            model.initialize();
            view.repaintGridPanel();
        }
    }
}
