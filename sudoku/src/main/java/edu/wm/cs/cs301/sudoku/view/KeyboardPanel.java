package edu.wm.cs.cs301.sudoku.view;

import edu.wm.cs.cs301.sudoku.model.SudokuPuzzle;
import edu.wm.cs.cs301.sudoku.controller.KeyboardButtonAction;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.KeyEvent;
import javax.swing.border.LineBorder;

/**
 * Creates on-screen keyboard buttons.
 * Maps physical and on-screen keyboard buttons to their
 * respective controller actions in KeyboardButtonAction.
 * @author Jack Stawasz
 */
public class KeyboardPanel {

    private final SudokuFrame view;
    private final SudokuPuzzle model;

    private final static int BUTTON_HEIGHT = 50;
    private final static int BUTTON_WIDTH = 50;
    private final static int BORDER_THICKNESS = 4;

    private final KeyboardButtonAction action;

    private final JPanel panel;

    KeyboardPanel(SudokuFrame view, SudokuPuzzle model) {
        this.view = view;
        this.model = model;
        this.panel = createMainPanel();
        this.action = new KeyboardButtonAction(view, model);
    }

    /**
     * Create container for keyboard items
     */
    private JPanel createMainPanel() {
        JPanel mainPanel = new JPanel();
        mainPanel.setFocusable(true);
        mainPanel.setLayout(new BoxLayout(mainPanel, BoxLayout.Y_AXIS));
        mainPanel.setBorder(BorderFactory.createEmptyBorder(10, 5, 0, 5));

        mainPanel.add(createNumPanel());
        mainPanel.add(Box.createVerticalStrut(10)); // White space
        mainPanel.add(createEditPanel());

        return mainPanel;
    }

    /**
     * Number panel of buttons for inserting selection values.
     */
    private JPanel createNumPanel() {
        JPanel panel = new JPanel(new GridLayout());
        panel.setBorder(new LineBorder(Color.BLACK, BORDER_THICKNESS));
        Font textfont =  new Font("Dialog", Font.PLAIN, 20);

        String[] numbers = new String[9];
        for(int i=0; i<9; i++) {
            numbers[i] = Integer.toString(i+1);
        }

        for (String number : numbers) {
            JButton button = new JButton(action);

            // Actions (keyboard and button)
            button.setActionCommand(number);
            setKeyBinding(button, number);
            button.addActionListener(e ->
                action.actionPerformed(new ActionEvent(button, ActionEvent.ACTION_PERFORMED, number))
            );

            button.setBackground(new Color(222, 220, 250)); // Light Blue RGB
            button.setBorder(BorderFactory.createLineBorder(new Color(170, 180, 240), BORDER_THICKNESS / 2)); // Light(ish) blue RGB
            button.setText(number);
            button.setPreferredSize(new Dimension(BUTTON_WIDTH, BUTTON_HEIGHT));
            button.setFont(textfont);
            panel.add(button);
        }

        return panel;
    }

    /**
     * Create buttons that interact with the model,
     * such as "Enter" and "Delete".
     */
    private JPanel createEditPanel() {
        JPanel panel = new JPanel(new GridLayout());
        panel.setBorder(new LineBorder(Color.BLACK, BORDER_THICKNESS));

        // Delete key
        JButton deleteButton = createEditButton("Delete");
        panel.add(deleteButton);

        // Enter key
        JButton enterButton = createEditButton("Enter");
        setKeyBinding(enterButton, "Enter");
        enterButton.addActionListener(e ->
            action.actionPerformed(new ActionEvent(enterButton, ActionEvent.ACTION_PERFORMED, "Enter"))
        );
        panel.add(enterButton);

        return panel;
    }

    /**
     * Create a single edit button for createEditPanel()
     */
    private JButton createEditButton(String text) {
        JButton button = new JButton(text);
        final Font textfont =  new Font("Dialog", Font.PLAIN, 30);

        // Set Appearance
        button.setPreferredSize(new Dimension(5*BUTTON_WIDTH, BUTTON_HEIGHT));
        button.setBackground(new Color(222, 220, 250)); // Light Blue RGB
        button.setBorder(BorderFactory.createLineBorder(new Color(170, 180, 240), BORDER_THICKNESS / 2)); // Light(ish) blue RGB
        button.setForeground(Color.BLACK); // AKA text color
        button.setFont(textfont);

        // Bind keyboard and button actions to KeyboardButtonAction
        setKeyBinding(button, text);
        button.addActionListener(e ->
            action.actionPerformed(new ActionEvent(button, ActionEvent.ACTION_PERFORMED, text))
        );

        return button;
    }

    /**
     * Map physical keyboard keys to KeyboardButtonAction
     */
    private void setKeyBinding(JButton button, String text) {
        InputMap inputMap = button.getInputMap(JButton.WHEN_IN_FOCUSED_WINDOW);
        ActionMap actionMap = button.getActionMap();

        // Identify keystroke and insert to inputMap
        KeyStroke keyStroke;
        if (text.equalsIgnoreCase("Delete")) { // Map backspace and delete keys
            keyStroke = KeyStroke.getKeyStroke(KeyEvent.VK_BACK_SPACE, 0);
            inputMap.put(keyStroke, text);
            keyStroke = KeyStroke.getKeyStroke(KeyEvent.VK_DELETE, 0);
        } else if (text.equalsIgnoreCase("Enter")) {
            keyStroke = KeyStroke.getKeyStroke(KeyEvent.VK_ENTER, 0);
        } else {
            keyStroke = KeyStroke.getKeyStroke(text);
        }
        inputMap.put(keyStroke, text);

        // Place action into action map
        Action action = new KeyboardButtonAction(view, model);
        actionMap.put(text, action);
    }

    public JPanel getPanel() {
        return this.panel;
    }
}
