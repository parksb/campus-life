import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;

public class EditorMotionListener implements MouseMotionListener {
    EditorClient editor;

    @Override
    public void mouseDragged(MouseEvent e) {
        if (!editor.getIsDrawMode()) {
            editor.modifyPoint(e.getX(), e.getY());
        }
    }

    @Override
    public void mouseMoved(MouseEvent e) {

    }
}
