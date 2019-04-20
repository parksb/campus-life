import java.awt.event.MouseListener;
import java.awt.event.MouseEvent;

public class MyDrawListener implements MouseListener {
    MyDrawPanel myPanel;

    public void mouseEntered(MouseEvent e) {}
    public void mouseExited(MouseEvent e) {}
    public void mousePressed(MouseEvent e) {}
    public void mouseClicked(MouseEvent e) {}

    public void mouseReleased(MouseEvent e) {
        myPanel.addPoint(new Point2D(e.getX(), e.getY()));
    }
}
