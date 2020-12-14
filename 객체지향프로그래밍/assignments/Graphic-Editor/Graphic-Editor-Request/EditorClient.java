import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.io.*;
import java.net.Socket;
import java.util.ArrayList;

public class EditorClient extends JPanel implements Serializable {

    private String titleName;
    private ArrayList<Point2D> points = new ArrayList<>();
    private DefaultListModel<String> pData = new DefaultListModel<>();

    private ObjectOutputStream writer;
    private ObjectInputStream reader;
    private Socket sock;
    private Point2D selectedPoint;
    private boolean isDrawMode = true;

    public EditorClient(Socket s, String name) {
        titleName = name;

        this.setUpNetworking(s);
        this.go();

        Thread t = new Thread(new Synchronizer());
        t.start();
    }

    public void sendAllData() {
        ArrayList<String> dataList = new ArrayList<>();
        try {
            for (int i = 0; i < pData.size(); i++) {
                dataList.add(pData.get(i));
            }

            writer.writeObject(points.clone());
            writer.writeObject(dataList.clone());

            writer.flush();
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    public void paintComponent(Graphics g) {
        int pointsLen = points.size();

        g.setColor(Color.white);
        g.fillRect(0, 0, this.getWidth(), this.getHeight());

        if (pointsLen > 0) {
            if (points.get(points.size() - 1).equals(selectedPoint)) {
                g.setColor(Color.red);
            } else {
                g.setColor(Color.black);
            }

            g.fillOval((int) points.get(pointsLen - 1).getX(), (int) points.get(pointsLen - 1).getY(), 10, 10);

            for (int i = 0; i < pointsLen - 1; i++) {
                int startPointX = (int) points.get(i).getX();
                int startPointY = (int) points.get(i).getY();

                if (points.get(i).equals(selectedPoint)) {
                    g.setColor(Color.red);
                } else {
                    g.setColor(Color.black);
                }

                g.fillOval(startPointX, startPointY, 10, 10);

                int endPointX = (int) points.get(i + 1).getX();
                int endPointY = (int) points.get(i + 1).getY();

                g.setColor(Color.black);
                g.drawLine(startPointX + 5, startPointY + 5, endPointX + 5, endPointY + 5);
            }
        }
    }

    public void addPoint(Point2D point) {
        points.add(point);
        pData.addElement("(" + Float.toString(point.getX()) + ", " + Float.toString(point.getY()) + ")");
        selectedPoint = point;

        this.sendAllData();
        this.repaint();
    }

    public void deletePoint(int idx) {
        if (idx >= 0) {
            points.remove(idx);
            pData.removeElementAt(idx);

            this.sendAllData();
            this.repaint();
        }
    }

    public void clearPoint() {
        while (!points.isEmpty() && !pData.isEmpty()) {
            if (!points.isEmpty()) {
                points.remove(0);
            }

            if (!pData.isEmpty()) {
                pData.removeElementAt(0);
            }
        }

        this.sendAllData();
        this.repaint();
    }

    public void modifyPoint(float x, float y) {
        for (int i = 0; i < points.size(); i++) {
            if (points.get(i).equals(selectedPoint)) {
                Point2D modifiedPoint = new Point2D(x, y);
                points.set(i, modifiedPoint);
                selectedPoint = modifiedPoint;
                break;
            }
        }

        pData.removeAllElements();
        for (Point2D p : points) {
            pData.addElement(String.valueOf(p.getX()) + ", " + String.valueOf(p.getY()));
        }

        this.repaint();
    }

    public void setSelectedPoint(float x, float y) {
        for (Point2D p : points) {
            if (x <= p.getX() + 10 && x >= p.getX()) {
                if (y <= p.getY() + 10 && y >= p.getY()) {
                    selectedPoint = p;
                    break;
                }
            }
        }

        this.repaint();
    }

    private boolean setUpNetworking(Socket s) {
        try {
            sock = s;
            writer = new ObjectOutputStream(sock.getOutputStream());
            reader = new ObjectInputStream(sock.getInputStream());
        } catch (IOException ex) {
            ex.printStackTrace();
            return false;
        }

        return true;
    }

    private void changeModeToSelect() {
        isDrawMode = false;
    }


    private void changeModeToDraw() {
        isDrawMode = true;
    }

    public boolean getIsDrawMode() {
        return isDrawMode;
    }

    public void go() {
        JFrame frame = new JFrame(titleName);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        EditorClient editor = this;
        EditorListener listener = new EditorListener();
        EditorMotionListener mlistener = new EditorMotionListener();
        listener.editor = this;
        mlistener.editor = this;
        editor.addMouseListener(listener);
        editor.addMouseMotionListener(mlistener);

        editor.setBorder(BorderFactory.createLineBorder(Color.black));
        frame.getContentPane().add(BorderLayout.CENTER, editor);

        JPanel panelPtsData = new JPanel();
        panelPtsData.setLayout(new BoxLayout(panelPtsData, BoxLayout.Y_AXIS));

        JList<String> listPtsData = new JList<String>(editor.pData);
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
                        editor.deletePoint(listPtsData.getSelectedIndex());
                    }
                }
        );

        JButton btnClear = new JButton("Clear");
        btnClear.addActionListener(
                new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                        editor.clearPoint();
                    }
                }
        );

        JRadioButton radDrawMode = new JRadioButton("Draw Mode", true);
        radDrawMode.addItemListener(new SelectItemListener());

        JRadioButton radSelectMode = new JRadioButton("Select Mode", true);
        radSelectMode.addItemListener(new SelectItemListener());

        ButtonGroup radGrp = new ButtonGroup();
        radGrp.add(radDrawMode);
        radGrp.add(radSelectMode);

        panelPtsData.add(btnDelete);
        panelPtsData.add(btnClear);
        panelPtsData.add(radDrawMode);
        panelPtsData.add(radSelectMode);
        panelPtsData.add(Box.createVerticalStrut(30));

        frame.getContentPane().add(BorderLayout.EAST, panelPtsData);
        BorderLayout layout = (BorderLayout) frame.getContentPane().getLayout();
        layout.setHgap(10);
        layout.setVgap(10);

        frame.setSize(800, 800);
        frame.setVisible(true);
    }

    class Synchronizer implements Runnable {
        public void run() {
            try {
                while (true) {
                    points = (ArrayList<Point2D>) reader.readObject();
                    ArrayList<String> data = (ArrayList<String>) reader.readObject();

                    pData.removeAllElements();
                    for (String s : data) {
                        pData.addElement(s);
                    }

                    repaint();
                }
            } catch (ClassNotFoundException | IOException ex) {
                ex.printStackTrace();
            }
        }
    }

    class SelectItemListener implements ItemListener {
        public void itemStateChanged(ItemEvent e) {
            AbstractButton selected = (AbstractButton) e.getItemSelectable();
            if (e.getStateChange() == ItemEvent.SELECTED) {
                if (selected.getText().equals("Draw Mode")) {
                    changeModeToDraw();
                } else {
                    changeModeToSelect();
                }
            }
        }
    }

}
