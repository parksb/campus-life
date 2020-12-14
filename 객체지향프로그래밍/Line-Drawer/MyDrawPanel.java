import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.event.MouseListener;
import java.util.ArrayList;

import javax.swing.DefaultListModel;
import javax.swing.JPanel;

public class MyDrawPanel extends JPanel {

	ArrayList<Point2D> points = new ArrayList();
	DefaultListModel<String> pData = new DefaultListModel<>();

	public void paintComponent(Graphics g) {
		int pointsLen = points.size() - 1;

		g.setColor(Color.white);
		g.fillRect(0, 0, this.getWidth(), this.getHeight());

		if (pointsLen > 0) {
			g.setColor(Color.black);

			for (int i = 0; i < pointsLen; i++) {
				int startPointX = (int) points.get(i).getX();
				int startPointY = (int) points.get(i).getY();
				int endPointX = (int) points.get(i + 1).getX();
				int endPointY = (int) points.get(i + 1).getY();

				g.drawLine(startPointX, startPointY, endPointX, endPointY);
			}
		}
	}

	public void addPoint(Point2D point) {
		points.add(point);
		pData.addElement("(" + Float.toString(point.getX()) + ", " + Float.toString(point.getY()) + ")");
		this.repaint();
	}

	public void deletePoint(int idx) {
		if (idx >= 0) {
			points.remove(idx);
			pData.removeElementAt(idx);
			this.repaint();
		}
	}
	
}
