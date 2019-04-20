import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleCannonBallGame {

    public static void main(String[] args) {
        SimpleCannonBallGame game = new SimpleCannonBallGame();
        game.go();
    }

    public void go() {
        JFrame frame = new JFrame("Cannon Ball Game");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        PlayView playPanel = new PlayView();

        JPanel controlPanel = new JPanel();
        controlPanel.setBorder(BorderFactory.createLineBorder(Color.black));

        JPanel buttonPanel = new JPanel();

        buttonPanel.setLayout(new BorderLayout());
        controlPanel.setLayout(new BorderLayout());

        JButton btnFire = new JButton("Fire");
        btnFire.setBackground(Color.red);
        btnFire.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Bomb newBomb = new Bomb();
                playPanel.addBomb(newBomb);
                playPanel.getCannon().fire(newBomb, playPanel.getTarget());
            }
        });

        JButton btnUp = new JButton("Up");
        btnUp.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                playPanel.getCannon().changeAngle(1.0);
            }
        });

        JButton btnDown = new JButton("Down");
        btnDown.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                playPanel.getCannon().changeAngle(-1.0);
            }
        });

        JButton btnLeft = new JButton("Left");
        btnLeft.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                playPanel.getCannon().takeXStep(10.0);
            }
        });

        JButton btnRight = new JButton("Right");
        btnRight.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                playPanel.getCannon().takeXStep(-10.0);
            }
        });

        buttonPanel.add(BorderLayout.NORTH, btnUp);
        buttonPanel.add(BorderLayout.EAST, btnLeft);
        buttonPanel.add(BorderLayout.CENTER, btnFire);
        buttonPanel.add(BorderLayout.WEST, btnRight);
        buttonPanel.add(BorderLayout.SOUTH, btnDown);

        controlPanel.add(BorderLayout.NORTH, buttonPanel);
        frame.getContentPane().add(BorderLayout.WEST, controlPanel);
        frame.getContentPane().add(BorderLayout.CENTER, playPanel);

        frame.setSize(1000, 500);
        frame.setVisible(true);
    }

}
