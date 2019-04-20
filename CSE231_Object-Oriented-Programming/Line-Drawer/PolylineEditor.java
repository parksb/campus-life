import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.BorderFactory;
import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.ScrollPaneConstants;

public class PolylineEditor {
    public static void main(String[] args) {
        // TODO Auto-generated method stub
        PolylineEditor gui = new PolylineEditor();
        gui.go();
    }

    public void go() {
        JFrame frame = new JFrame("Polyline Editor");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        MyDrawPanel drawPanel = new MyDrawPanel();
        MyDrawListener listener = new MyDrawListener();
        listener.myPanel = drawPanel;
        drawPanel.addMouseListener(listener);

        drawPanel.setBorder(BorderFactory.createLineBorder(Color.black));
        frame.getContentPane().add(BorderLayout.CENTER, drawPanel);

        JPanel panelPtsData = new JPanel();
        panelPtsData.setLayout(new BoxLayout(panelPtsData, BoxLayout.Y_AXIS));

        JList<String> listPtsData = new JList<String>(drawPanel.pData);
        listPtsData.setVisibleRowCount(10);

        JScrollPane scrollPtsList = new JScrollPane(listPtsData);
        scrollPtsList.setPreferredSize(new Dimension(100, 100));
        scrollPtsList.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
        scrollPtsList.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED);

        panelPtsData.add(Box.createVerticalStrut(10));

        panelPtsData.add(scrollPtsList);

        panelPtsData.add(Box.createVerticalStrut(30));

        JButton btnDelete = new JButton("Delete");
        btnDelete.addActionListener(
                new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                        drawPanel.deletePoint(listPtsData.getSelectedIndex());
                    }
                }
        );


        panelPtsData.add(btnDelete);
        panelPtsData.add(Box.createVerticalStrut(30));

        frame.getContentPane().add(BorderLayout.EAST, panelPtsData);
        BorderLayout layout = (BorderLayout) frame.getContentPane().getLayout();
        layout.setHgap(10);
        layout.setVgap(10);

        frame.setSize(800, 800);
        frame.setVisible(true);
    }


}
