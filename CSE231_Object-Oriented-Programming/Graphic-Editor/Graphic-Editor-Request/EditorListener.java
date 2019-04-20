import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

public class EditorListener implements MouseListener {
    EditorClient editor;

    @Override
    public void mouseClicked(MouseEvent e) {
        if (!editor.getIsDrawMode()) {
            editor.setSelectedPoint(e.getX(), e.getY());
        }
    }

    @Override
    public void mouseEntered(MouseEvent e) {

    }

    @Override
    public void mouseExited(MouseEvent e) {

    }

    @Override
    public void mousePressed(MouseEvent e) {

    }

    @Override
    public void mouseReleased(MouseEvent e) {
        if (editor.getIsDrawMode()) {
            editor.addPoint(new Point2D(e.getX(), e.getY()));
        } else {
            editor.sendAllData();
        }
    }
}
